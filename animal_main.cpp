/**
 * My Vu
 * This is a game that guesses an animal you are thinking about. If the animal
 * is not in the database, user is prompted with a question that helps the game
 * guess that animal in the next game and update itself with the added animal.
 * The game saves all the animal in a binary tree where each leaf node is an
 * animal and every other node is a yes/no question. The question from the parent
 * node is asked and if the answer is yes, it proceeds to ask the question of
 * the left child and right child, otherwise. It will keep asking questions until
 * it reaches the leaf node which results in an animal.
 */

#include <iostream>
#include "animal_tree.h"
using namespace std;


int main()
{
  const string FILE_NAME = "Animals.txt";

  // Construct a tree for the game
  Animal_tree animal( FILE_NAME );

  cout << "Welcome to animal guessing!" << endl << endl;

  // Variables to control when to stop the game
  string again_input = "y";
  bool play_again = true;

  // Game start
  while( play_again )
  {
    cout << "----------------------\n      Game Start\n----------------------"
         << endl;
    cout << "Think about an animal, I'll guess it!" << endl;
    cout << "Press enter when you're ready!" << endl;
    cin.get();
    cout << "Okay, let's start!" << endl;

    // Asking questions and adding more animal if needed
    animal.ask_question( animal.get_root_node() );

    cout << endl << endl;

    // Decide whether the user wants to play again
    while( true )
    {
      cout << "Do you want to play again?(y/n) ---> ";
      getline(cin, again_input);
      if( again_input == "N" || again_input == "n" )
      {
        play_again = false;
        break;
      }
      else if( again_input == "Y" || again_input == "y" )
      {
        play_again = true;
        break;
      }
      else
      {
        cout << "Wrong input! ";
      }
    }
    cout << endl << endl;
  }

  // Save information from the tree to the save file
  animal.save_data( FILE_NAME );

  // destruct the tree
  animal.delete_tree( animal.get_root_node() );

  return 0;
}
