#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
using namespace std; //Implementing namespace std enables the use of code such as cout and cin without needing to add std:: making it more efficient.

class Player {

protected: //Protected visibility modifier used to allow methods to be used only within the Player class and parented classes.
    string Name;
    int Health = 0;
    string Attack1;
    int Attack1Damage = 0;
    string Attack2;
    int Attack2Damage = 0;
    int SpecialAttackDamage = 0;

    
public: // Public visibility modifier is used here to allow the methods to be used anywhere.
    // Set value procedures are used to more easily set certain values shared with multiple objects without needing to re-write the code.
    void setValues(string name, int health, string attack1, int attack1Damage, string attack2, int attack2Damage) {
        Name = name; Health = health; Attack1 = attack1; Attack1Damage = attack1Damage; Attack2 = attack2; Attack2Damage = attack2Damage;
    }

    void setHealth(int healthTaken)
    {
        Health = Health - healthTaken;
    }

    // Get value function which takes the object and returns the defined variables.
    string getName() { return Name; }
    int getHealth() { return Health; }
    string getAttack1() { return Attack1; }
    int getAttack1Damage() { return Attack1Damage; }
    string getAttack2() { return Attack2; }
    int getAttack2Damage() { return Attack2Damage; }

    //ATTACKS
    // Each attack has its own function to shorten the code each time an attack is carried out.
    // Overriding is used here where two Attack functions are present with different parameters to determine the one used.
    int Attack(int number) {
        int playerDamage = 0;
        playerDamage = rand() % Attack1Damage;
        return playerDamage;
    };

    int Attack(string number) {
        int playerDamage = 0;
        playerDamage = rand() % Attack2Damage, Attack2Damage - 20;
        return playerDamage;
    };
};

// Class Rival is a child class to the Player class which means it inherits all the functions and variables within the Player class as well as it's own.
class Rival : public Player {
public:
    // Overloading is used here with setValues as it is the same Function used but with different classes, rival class includes a special attack damage identifier.
    void setValues(string name, int health, string attack1, int attack1Damage, string attack2, int attack2Damage, int specialAttackDamage) {
        Name = name; Health = health; Attack1 = attack1; Attack1Damage = attack1Damage; Attack2 = attack2; Attack2Damage = attack2Damage; SpecialAttackDamage = specialAttackDamage;
    }
    // Rival attacks are used to make the Rival class independant and cannot be accessed by the Player class.
    int specialAttack() {
        int playerDamage = 0;
        playerDamage = rand() % 45, SpecialAttackDamage;
        return playerDamage;
    };

};




// START OF GAME
// This is where the code for the game begins and the user begins to interact and input values.
int main()
{
    srand(static_cast<unsigned int>(std::time(nullptr))); // srand() is used here to make sure that rand() when used is completely random each time.
    Player playersFighter;
    Rival rivalsFighter;
    string playerName;
    ofstream MyFile("Battle.txt");
    cout << "Hello traveller! What is your name?\n";
    cin >> playerName; // The user inputs their name for later use in the code.

    cout << "Hello " << playerName << "! Welcome to the battle arena, choose a fighter to accompany you in your battles!\n1 - Chris Rock\n2 - Will Smith\n3 - The Rock\n";

    // This is where the player chooses their fighter to battle with, using a switch case of 1, 2 or 3 to pick.
    int choice = 0;
    while (choice != 3 && choice != 2 && choice != 1)
    {
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "You have chosen.. Chris Rock!\n\n-\n\n";
            playersFighter.setValues("Chris Rock", 100, "Offensive Punchline", 40, "Bald Deflect", 50); //Each case uses the setValues code to set the values of the playersFighter and rivalsFighter objects.
            rivalsFighter.setValues("Will Smith", 100, "Left, Right, Goodnight", 30, "Defend Wife", 70, 80);
            break;
        case 2:
            cout << "You have chosen.. Will Smith!\n\n-\n\n";
            playersFighter.setValues("Will Smith", 100, "Left, Right, Goodnight", 30, "Defend Wife", 70);
            rivalsFighter.setValues("The Rock", 100, "He Gon' Rumble", 40, "Take Yo Face Off", 60, 70);
            break;
        case 3:
            cout << "You have chosen.. The Rock!\n\n-\n\n";
            playersFighter.setValues("The Rock", 100, "He Gon' Rumble", 40, "Take Yo Face Off", 60);
            rivalsFighter.setValues("Chris Rock", 100, "Offensive Punchline", 40, "Bald Deflect", 50, 60);
            break;
        default:
            cout << "Please enter a valid number. (1-3)" << endl; // The user is informed if their number is invalid through the default switch case.
            break;
        }
    }
    // The code then outputs the players stats and the rivals stats such as attacks and health.
    cout << "Player Stats:\nFighter // " << playersFighter.getName() << "\nHealth // " << playersFighter.getHealth() << "\nPrimary Attack //  " << playersFighter.getAttack1() << "\nPA Damage // " << playersFighter.getAttack1Damage() << "\nSecondary Attack // " << playersFighter.getAttack2() << "\nSA Damage // " << playersFighter.getAttack2Damage() << "\n\n";
    cout << "Rival Stats:\nFighter // " << rivalsFighter.getName() << "\nHealth // " << rivalsFighter.getHealth() << "\nPrimary Attack //  " << rivalsFighter.getAttack1() << "\nPA Damage // " << rivalsFighter.getAttack1Damage() << "\nSecondary Attack // " << rivalsFighter.getAttack2() << "\nSA Damage // " << rivalsFighter.getAttack2Damage() << "\n\n";
    // These are variables defined which are used in the battle.
    int chosenAttack = 0;
    int rivalsAttack;
    bool gameOver = false;
    int roundCount = 0;
    
    // BATTLE ROUND LOOP
    // Loop put in place to loop the battle every time until either the player or the rival has below 0 health.
    while (gameOver == false) {
        roundCount++;
        cout << "FIGHT!\nChoose your attack!\n1. " << playersFighter.getAttack1() << "\n2. " << playersFighter.getAttack2() << "\n3. Run Away" << endl;
        while (chosenAttack != 1 && chosenAttack != 2) // A while loop is used here to ensure that the attack the player chooses is between 1 and 2, a validation check.
        {
            cin >> chosenAttack;
            switch (chosenAttack) // The switch case here is used to let the player choose the attack they wish to use against their opponent.
            {
            case 1:
                system("cls");
                cout << "--------- Turn " << roundCount << " -------------\n\n";
                MyFile << "--------- Turn " << roundCount << " -------------\n\n";
                cout << "Your Move:\n";
                cout << playersFighter.getName() << " uses.. " << playersFighter.getAttack1() << "!\n\n";
                MyFile << playersFighter.getName() << " uses.. " << playersFighter.getAttack1() << "!\n\n"; // Outputs the players attack to both the console and the file.
                rivalsFighter.setHealth(playersFighter.Attack(1)); // The rival object uses setHealth code combined with the primaryAttack code to deduct the health amount from the rival inwhich the attack does.
                break;
            case 2:
                system("cls");
                cout << "--------- Turn " << roundCount << " -------------\n\n";
                MyFile << "--------- Turn " << roundCount << " -------------\n\n";
                cout << "Your Move:\n";
                cout << playersFighter.getName() << " uses.. " << playersFighter.getAttack2() << "!\n\n";
                MyFile << playersFighter.getName() << " uses.. " << playersFighter.getAttack2() << "!\n\n";
                rivalsFighter.setHealth(playersFighter.Attack("two"));
                break;
            case 3:
                cout << "You have fled the battle! Lame." << endl;
                return 0;
            default:
                cout << "Invalid number! (1 or 2)\n"; // The default case used as the else statement to tell the user if their number is invalid.
                break;
            }
        }
        cout << "Rival Stats:\nFighter // " << rivalsFighter.getName() << "\nHealth // " << rivalsFighter.getHealth() << "\n\n"; // This outputs the rivals stats after being dealt the attack.
        MyFile << "Rival Stats:\nFighter // " << rivalsFighter.getName() << "\nHealth // " << rivalsFighter.getHealth() << "\n\n";

        if (rivalsFighter.getHealth() <= 0) // Checks to see if the rivals health is less than 0, if so the game is complete and a winning message is displayed with the finish stats of the player.
        {
            cout << "Your Finishing Stats: \nFighter // " << playersFighter.getName() << "\nHealth // " << playersFighter.getHealth() << "\n\n";
            MyFile << "Your Finishing Stats: \nFighter // " << playersFighter.getName() << "\nHealth // " << playersFighter.getHealth() << "\n\n";
            gameOver = true;
            cout << "Congratulations! You beat " << rivalsFighter.getName() << ", pat yourself on the back!";
            MyFile << "Congratulations! You beat " << rivalsFighter.getName() << ", pat yourself on the back!"; // The winning message is displayed to the user through the battle.txt file.
            MyFile.close();
        }

        else // The else statement here continues the game if the player has not yet won.
        {
            chosenAttack = 0;
            rivalsAttack = rand() % 3 + 1; // A random number is generated here to choose which attack the rival uses.
            switch (rivalsAttack) { // The rival is given 3 options for attacks, the regular inherited primary and secondary attack, but also a special attack which can only be used by the rival.
            case 1:
                cout << "Rivals Move:\n\n";
                cout << rivalsFighter.getName() << " uses.. " << rivalsFighter.getAttack1() << "!\n\n";
                MyFile << rivalsFighter.getName() << " uses.. " << rivalsFighter.getAttack1() << "!\n\n";
                playersFighter.setHealth(rivalsFighter.Attack(1));
                break;
            case 2:
                cout << "Rivals Move:\n";
                cout << rivalsFighter.getName() << " uses.. " << rivalsFighter.getAttack2() << "!\n\n";
                MyFile << rivalsFighter.getName() << " uses.. " << rivalsFighter.getAttack2() << "!\n\n";
                playersFighter.setHealth(rivalsFighter.Attack("two"));
                break;
            case 3:
                cout << "Rivals Move:\n";
                cout << rivalsFighter.getName() << " uses.. " << rivalsFighter.getAttack2() << " (Special)!\n\n";
                MyFile << rivalsFighter.getName() << " uses.. " << rivalsFighter.getAttack2() << " (Special)!\n\n";
                playersFighter.setHealth(rivalsFighter.specialAttack());
                break;
            }
            cout << "Player Stats:\nFighter // " << playersFighter.getName() << "\nHealth // " << playersFighter.getHealth() << "\n\n"; //After the rivals move the players stats are presented to the user.
            MyFile << "Player Stats:\nFighter // " << playersFighter.getName() << "\nHealth // " << playersFighter.getHealth() << "\n\n"; // These stats are also presented in the battle.txt file.

            if (playersFighter.getHealth() <= 0) // Checks to see if the player has less than 0 health and if so proceeds to inform the player of their loss.
            {
                gameOver = true;
                cout << "Looks like you were beaten by " << rivalsFighter.getName() << ", better luck next time!";
                MyFile << "Looks like you were beaten by " << rivalsFighter.getName() << ", better luck next time!";
                MyFile.close(); // The text file is then closed so that the code can no longer access it.
            }
        }
    }
}