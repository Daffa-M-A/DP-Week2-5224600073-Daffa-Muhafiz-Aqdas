# DP-Week2-5224600073-Daffa-Muhafiz-Aqdas

Core Loop - Stone Skipping
1. System initializes state: Permainan menyiapkan kaleng (deck) berisi batu acak dan membagikan 5 batu ke hand pemain.

2. Pemain memilih untuk memainkan 1-3 batu atau membuang batu dari tangan.

3. a. Jika Play: Sistem menghitung jumlah pantulan (skipping) berdasarkan interaksi power (base/smoothness) dan friction dari batu yang dilempar.

b. Jika Discard: Sistem membuang batu yang dipilih.

4. Sistem menarik batu baru dari can untuk mengisi hand dan mengurangi sisa Plays/Discards. Jika pemain melakukan Play, skor akan ditambahkan ke total skor saat ini.

5. Sistem mengecek apakah pemain sudah mencapai target skor ronde tersebut atau kehabisan batas Play.

6. Jika pemain menang, pemain masuk ke Shop untuk memilih Leaf (modifier) baru yang akan mengubah aturan perhitungan skor batu di ronde selanjutnya.

7. Proses diulang ke ronde berikutnya hingga 3 ronde selesai.

Invariant - Stone Skipping
1. Which steps in your loop must NEVER change order?
Urutan Play dari player -> Menghitung skor -> State Update -> Reward (Shop) tidak boleh untuk diubah.

2. Which components must always exist for the game to function?
Class RunSession dan class ScoringSystem wajib selalu ada. Objek Stone juga menjadi entitas yang harus tetap ada di antara kedua sistem ini.

3. What would break if the order changes?
Jika Scoring dihitung sebelum player melakukan play hand, sistem akan mengkalkulasi nilai kosong. Jika Shop diletakkan sebelum Evaluate Condition, pemain bisa mendapatkan upgrade Leaf tanpa perlu membuktikan mereka bisa mengalahkan ronde tersebut terlebih dahulu, menghancurkan progresi dan tantangan game.

Mutable -Stone Skipping
1. Stone Properties (Base Value & Friction): Nilai Igneous = 0.2 friction, Sedimentary = 7 base value adalah data fleksibel. Mengubah angka ini dapat mengubah cara bermain, tetapi tidak akan merusak rumus pantulan utama di ScoringSystem.

2. Leaf Modifier: Kemampuan seperti Burning Leaf (mengurangi friction) atau Floating Leaf (peluang pantul ekstra) bisa ditambah, dikurangi, atau diubah efeknya kapan saja tanpa mengganggu loop permainan utama.

3. Round Targets & Limits: Target skor serta jumlah maksimal Play/Discard adalah metrik yang mengatur keseimbangan tingkat kesulitan. Ini bisa diubah dinamis.

1. What is the invariant structure of your game?
Struktur invariant dari game ini adalah urutan eksekusi core loop yang terdapat di class RunSession yang secara konstan menggerakkan progres pemain. Siklus ini secara harus berjalan dari: Inisialisasi Ronde (pembuatan deck dan hand) -> Aksi Pemain (memilih batu untuk dimainkan) -> Resolusi Sistem (kalkulasi pantulan dan gesekan oleh sistem scoring) -> Pembaruan Status (pengurangan sisa giliran) -> Evaluasi Kondisi (mengecek pencapaian target) -> Fase Reward (pemilihan Leaf di Shop jika pemain menang). Struktur ini adalah fondasi utama yang mengatur kapan sistem diizinkan untuk melakuan sebuah proses di dalam game.

2. What parts are mutable?
Bagian yang mutable adalah elemen-elemen mekanik, parameter stat, dan variasi konten yang menentukan dinamika game. Contoh utamanya adalah probabilitas kemunculan jenis batu, nilai base smoothness dan friction dari setiap batu, serta rumus kalkulasi penambahan skor akhir. Efek spesifik dari setiap modifier Leaf yang ada di Shop juga merupakan elemen mutable. Parameter seperti target skor setiap ronde dan batas interaksi pemain dirancang agar mudah dimodifikasi (scaling) tanpa perlu membongkar ulang kerangka arsitektur utama.

3. If you wanted to add a new feature, which class would change?
Fleksibilitas sistem memungkinkan penambahan fitur baru melalui modifikasi kode seminimal mungkin. Misalnya, jika saya ingin menambahkan jenis Leaf baru dengan efek unik seperti menghilangkan friction sepenuhnya, saya hanya perlu membuat class baru yang mewarisi interface IModifier dan mendaftarkannya di dalam kelas ModifierFactory. Kelas inti permainan seperti RunSession dan ScoringSystem sama sekali tidak perlu disentuh, karena mereka dirancang untuk menerima deretan modifier secara dinamis, bukan secara eksplisit merujuk pada jenis Leaf tertentu.

4. If you changed the loop order, what would break?
Jika urutan loop invariant ini diubah, integritas sistem permainan akan hancur dan menghasilkan bug beruntun. Sebagai contoh, jika System rkalkulasi skor dieksekusi sebelum Player action, sistem scoring akan mencoba memproses sekumpulan data batu kosong, menghasilkan perolehan nilai nol. Demikian pula, jika fase Shop diletakkan mendahului Evaluasi Kondisi, pemain akan memiliki akses untuk membeli dan melengkapi Leaf dari Shop tanpa perlu mencapai target skor ronde tersebut, yang secara langsung merusak progresi dan esensi tantangan dari permainan itu sendiri.