#include <iostream>

class ScoringSystem {
public:
    void CalculateScore() {
        std::cout << "  [System] Calculating bounces based on stone power and friction...\n";
        std::cout << "  [System] Updating total score.\n";
    }
};

class ShopSystem {
public:
    void OpenShop() {
        std::cout << "\n  [Shop] Presenting Leaves (Modifiers) to the player...\n";
        std::cout << "  [Shop] Player selects and acquires a new Leaf.\n";
    }
};

class RunSession {
private:
    bool roundCleared = false;
    bool gameOver = false;
    ScoringSystem scorer;
    ShopSystem shop;
    int currentRound = 1;
    const int MAX_ROUNDS = 3;

public:
    void StartRound() {
        std::cout << "\n=== ROUND " << currentRound << " STARTS ===\n";
        std::cout << "[System] Generating Stone Can (Deck) and drawing Hand.\n";
        roundCleared = false;
    }

    void PlayerAction() {
        std::cout << "\n[Player] Chooses to Play 1-3 stones or Discard.\n";
    }

    void ResolveSystem() {
        scorer.CalculateScore();
    }

    void UpdateState() {
        std::cout << "[System] Decreasing remaining plays/discards. Drawing new stones.\n";
        
        // Placeholder logika menang/kalah
        std::cout << "[System] Checking if target score is reached...\n";
        
        // Simulasi pemain mencapai target skor
        roundCleared = true; 
    }

    void RewardPhase() {
        if (currentRound < MAX_ROUNDS) {
            shop.OpenShop();
        }
    }

    bool IsRoundCleared() const { return roundCleared; }
    bool IsGameOver() const { return gameOver || currentRound > MAX_ROUNDS; }
    
    void NextRound() { currentRound++; }
};

// --- MAIN EXECUTION ---

int main() {
    RunSession session;

    std::cout << "Game Started!\n";

    while (!session.IsGameOver()) {
        session.StartRound();

        // The Core Loop per round (Invariant Structure)
        while (!session.IsRoundCleared() && !session.IsGameOver()) {
            session.PlayerAction();
            session.ResolveSystem();
            session.UpdateState();
        }

        if (session.IsRoundCleared()) {
            session.RewardPhase();
            session.NextRound();
        }
    }

    std::cout << "\n[Game Over] Run Finished!\n";
    return 0;
}