#ifndef ANIMAL_TREE_H
#define ANIMAL_TREE_H

#include <fstream>

/**
 * This class is a binary tree where each leaf node store an animal and every
 * other node stores a question to help guess that animal.
 */
class Animal_tree
{
private:
  // A structure for a node of the tree
  struct tree_node
  {
    std::string question; // The question of that node
    unsigned num; // The number to decide children and parent node
    tree_node* left = nullptr; // Pointer to the left node
    tree_node* right = nullptr; // Pointer to the right node
  };
  tree_node* root_node = nullptr; // The root node of the tree
  std::ifstream data_file; // File object to read in information
  std::ofstream save_file; // File object to save information to a text file

public:
  // default constructors
  Animal_tree();

  /**
    Parameters: file_name - name of the save file
    Function: a constructor that open the input file object and facilitate the
              root node of the tree with data from the file
  */
  Animal_tree( std::string file_name );

  /**
    Parameters: current_num - number value of the node in the current iteration
                current_ptr - pointer to the node in the current iteration
    Function: Recursively transfer saved information from the save file to the
              trees

  */
  unsigned read_to_tree( unsigned current_num, tree_node* current_ptr );

  // -------------- accessors ----------------
  tree_node* get_root_node() const;

  /**
    Parameters: node_ptr - pointer to the current tree node that travels along
                the tree as the questions are being asked
    Function: A recursive function that asks the questions to find out what the
              animal is. If the animal is unknown, add that to the tree with
              the right question.
  */
  void ask_question( tree_node* node_ptr );

  /**
    Parameters: current_node - pointer to the node that needs modification to
                add another animal
    Function: when an animal is not in the tree, prompt the user for a question
              that distinguish the wrong guess from the new animal and modify
              the node accordingly
  */
  void add_animal( tree_node* current_node );

  /**
    Parameters: current_node - pointer to the node in the current iteration
    Function: A recursive function that write the data from the tree to a file
              in pre-order traversal
  */
  void write_to_file( tree_node* current_node );

  /**
    Parameters: file_name - name of the save file
    Function: open, write to, and close the save file
  */
  void save_data( std::string file_name );

  /**
    Parameters: current_mode - pointer to the node in the current iteration
                indent - number of indent to distinguish children and parent
    Function: A recursive function that nicely print the tree to the console
    NOTE: not needed in the program, just for testing
  */
  void print( tree_node* current_node, size_t indent = 0 );

  /**
    Parameters: num - the number value of the new node
                question - the question value of the new node
    Return: the pointer to the newly created node
    Function: construct a new node and return a pointer to it
  */
  tree_node* append_node( unsigned num, std::string question );

  /**
    Return: true if the user inputs yes, false if the user inputs no
    Function: save user's yes no input and handle the exception in case the
              user's input is invalid
  */
  bool input_yes_no();

  /**
    Parameters: current_node - the tree node used in the current iterator
    Function: A recursive function that delete all the tree nodes from the
              memory
  */
  void delete_tree( tree_node* current_node );

  // Destructor
  ~Animal_tree();


}; // end animal_tree class header

#endif // ANIMAL_TREE_H
