#include "animal_tree.h"
#include <fstream>
#include <iostream>

using namespace std;

Animal_tree::Animal_tree( string file_name )
{
  data_file.open( file_name ); // open save file

  // Create and facilitate the root node
  unsigned root_num;
  string root_question;
  data_file >> root_num;
  data_file.ignore();
  getline( data_file, root_question );
  root_node = append_node( root_num, root_question );

  // Transfer data from save file to the created tree
  read_to_tree( root_node->num, root_node );

  data_file.close();// Close data_file
}

Animal_tree::tree_node* Animal_tree::get_root_node() const
{
  return root_node;
}


unsigned Animal_tree::read_to_tree(  unsigned current_num,
                                     tree_node* current_ptr )
{
  unsigned next_num;
  string next_question;
  if( data_file >> next_num )
  {
    getline( data_file, next_question );

    // create and append to the left of current node
    if ( next_num == 2 * current_num )
    {
      getline( data_file, next_question );
      current_ptr->left = append_node( next_num, next_question );
      next_num = read_to_tree( next_num, current_ptr->left );
    }// end if

    // create and append to the right of current node
    if ( next_num == ( 2 * current_num ) + 1 )
    {
      getline( data_file, next_question );
      current_ptr->right = append_node( next_num, next_question );
      next_num = read_to_tree( next_num, current_ptr->right );
    }// end if
    return next_num;
  }// end if
  else
  {
    return 0; // BASE CASE
  }
}

void Animal_tree::print( tree_node* current_node, size_t indent )
{
  // Better visualize the tree by adding white space
  if( current_node != nullptr )
  {
    for( size_t i = 0 ; i < indent; ++i )
    {
      cout << "\t";
    }
    cout << current_node->num << ": " << current_node->question << endl;
    print( current_node->left, indent + 1 );
    print( current_node->right, indent + 1 );
  }// end if
  // BASE CASE: do nothing
}

void Animal_tree::ask_question( tree_node* node_ptr )
{
  if( node_ptr != nullptr )
  {
    cout << " + " << node_ptr->question << "(y/n) ---> "; // print question
    bool try_again = true;
    bool user_choice = false;

    // Handle exception if user input something wrong
    while( try_again )
    {
      try
      {
        user_choice = input_yes_no();
        try_again = false;
      }
      catch( string wrong_input )
      {
        cout << wrong_input;
      }
    }// end while

    cout << endl;

    if( user_choice ) // When the user answer Yes
    {
      // If there's no child, we have guessed the animal
      if( node_ptr->right == nullptr )
      {
        cout << endl;
        cout << "=-=-=-= Nice! I guessed it! =-=-=-=" << endl;
      }// end if
      // If there's a right child, go to that right node
      else
      {
        ask_question( node_ptr->right );
      }// end else
    }// end if
    else // When the user answer No
    {
      // If there's no child, we need to add that new animal
      if( node_ptr->left == nullptr )
      {
        add_animal( node_ptr );
        cout << endl;
        cout << "=-=-=-= Nice! Now I know another animal! =-=-=-=" << endl;
      }
      // If there's a left child, go to that left node
      else
      {
        ask_question( node_ptr->left );
      }
    }// end else
  }// end if
  // BASE CASE: Do nothing
}

void Animal_tree::add_animal( tree_node* current_node )
{
  // prompt and save the new animal's name
  cout << "I don't know this animal. What is it? ---> ";
  string new_name = "";
  getline( cin, new_name );
  // If the user capitalize the first letter, make it not capitalize
  new_name[0] = static_cast<char>(tolower(new_name[0]));
  cout << endl;

  // Prompt the user for the distinguishing question and save it
  cout << "I need a question to distinguish " << new_name <<
       " from my guess. " << endl;
  cout << "Please enter the question ---> ";
  string new_question = "";
  getline( cin, new_question );
  // capitalize the first letter
  new_question[0] = static_cast<char>(toupper(new_question[0]));
  if(new_question.back() != '?') // add "?" at the end if not exist
  {
    new_question = new_question + "?";
  }

  // Prompt the user for the correct answer and catch the wrong input exception
  cout << endl;
  cout << "What is the correct answer for " << new_name << "?(y,n) ---> ";
  bool try_again = true;
  bool user_choice = false;
  while( try_again )
  {
    try
    {
      user_choice = input_yes_no();
      try_again = false;
    }
    catch( string wrong_input )
    {
      cout << wrong_input;
    }
  }// end while

  // Create and append node accordingly
  if( user_choice )
  {
    // add the new animal to the right of current node
    current_node->right = append_node( ( current_node->num ) * 2 + 1, "Is it a " + new_name + "?" );

    // move the animal in the current node to the left of the current node
    current_node->left = append_node( ( current_node->num ) * 2, current_node->question );
  }// end if
  else
  {
    // add the new animal to the right of current node
    current_node->left = append_node( ( current_node->num ) * 2, "Is it a " + new_name + "?" );

    // move the animal in the current node to the left of the current node
    current_node->right = append_node( ( current_node->num ) * 2 + 1, current_node->question );

  }
  // change the question of the current node
  current_node->question = new_question;
}

void Animal_tree::write_to_file( tree_node* current_node )
{
  if( current_node != nullptr  )
  {
    save_file << current_node->num << endl;
    save_file << current_node->question << endl;
    write_to_file( current_node->left );
    write_to_file( current_node->right );
  }// end if
  // BASE CASE: Do nothing
}

void Animal_tree::delete_tree( tree_node* current_node )
{
  if( current_node->left != nullptr )
  {
    delete_tree( current_node->left );
    delete_tree( current_node->right );
  }
  // BASE CASE:
  delete current_node;
  current_node = nullptr;
}

bool Animal_tree::input_yes_no()
{
  string input;
  getline( cin, input );
  if ( input == "y" || input == "Y" )
  {
    return true;
  }
  else if( input == "n" || input == "N" )
  {
    return false;
  }
  else
  {
    string wrong_input = "ERROR: Wrong input, please try again(y/n)---> ";
    throw wrong_input;
  }
}

Animal_tree::tree_node* Animal_tree::append_node( unsigned num,
    string question )
{
  // Create new node with data from the arguments
  tree_node* new_node = new tree_node;
  new_node->num = num;
  new_node->question = question;

  return new_node;
}

void Animal_tree::save_data( string file_name )
{
  save_file.open( file_name );
  write_to_file( root_node );
  save_file.close();
}

Animal_tree::~Animal_tree()
{
  delete_tree( root_node );
}
