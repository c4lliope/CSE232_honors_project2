#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <random>
#include <map>
#include <sstream>
#include <fstream>
#include <string>
#include <iterator>

using std::vector;
using std::advance;
using std::string;
using std::deque;
using std::to_string;
using std::default_random_engine;
using std::uniform_int_distribution; using std::default_random_engine;
using std::istringstream;
using std::ifstream;
using std::ofstream;
using std::cout; using std::endl; using std::cin;
using std::size_t;
using std::map;
using std::ostream;
using std::pair;


struct Die{
  //default_random_engine dre;
  public:
    long values_ = 6;

    long roll(default_random_engine &dre){
      uniform_int_distribution<long> dice_dist(1,values_);
      long return_val;
      return_val = dice_dist(dre);
      cout << return_val << ", "; 
      return return_val;
    }//of roll
};//of Die

struct Space{
  public:
    int h_index_;
    int v_index_;
    vector<Die> dice_;
    Space *up_;
    Space *down_;
    Space *left_;
    Space *right_;

    void add_die(Die die){
      if(dice_.size() < 7)
        dice_.push_back(die);
    }

    void attack(Space &s1, Space &s2,default_random_engine &dre,Die die){
      long s1_score=0; long s1_roll;
      long s2_score=0; long s2_roll;
      cout << "Player 1's rolls: ";
      for(auto elem:s1.dice_){
        s1_score += die.roll(dre); 
        cout << s1_score << ", ";
      }
      cout << "Player 2's rolls: ";
      for(auto elem:s2.dice_){
        s2_score += die.roll(dre); 
        cout << s2_score << ", ";
      }
    }///of attack

    Space(int h,int v){
      h_index_ = h;
      v_index_ = v;
    }//of constructor

};//of space      

struct Player{
  public:
    vector< Space* > player_spaces_;
};//of Player

struct Grid{
  private:
    vector< vector< Space* > > grid_;
    int const h_rows_ = 6;
    int const v_columns_ = 6;
    long const total_spaces_ = 36;
  public:


    Grid(){
      for (int h = 0; h < h_rows_; h++) {
        // add a new row
        vector< Space* > row_h;
        row_h.clear();
        grid_.push_back(row_h);

        for (int v = 0; v < v_columns_; v++) {
          Space *set_space = new Space(h, v); // these arguments might be backwards
          row_h.push_back(set_space);

          //middle cases
          if ((h != 0) && (h != 5) && (v != 5) && (v != 0)){
            cout << "Middle case" << endl;
            if (set_space->up_ == nullptr)
              set_space->up_ = new Space(h,v+1);
            if (set_space->down_ == nullptr)
              set_space->down_ = new Space(h,v-1);
            if (set_space->right_ == nullptr)
              set_space->right_ = new Space(h+1,v);
            if (set_space->left_ == nullptr)
              set_space->left_ = new Space(h-1,v);
          }//of if

          //non-middle cases
          else{
            cout << "Corner Case "<< endl;
            if (h == 0 && v == 0){
              set_space->left_ == nullptr;
              set_space->down_ == nullptr;}
            if (h == 0 && v == 5){
              set_space->left_ == nullptr;
              set_space->up_ == nullptr;}
            if (h == 5 && v == 0){
              set_space->right_ == nullptr;
              set_space->up_ == nullptr;}
            if (h == 5 && v == 5){
              set_space->right_ == nullptr;
              set_space->down_ == nullptr;}

            //edge-only cases
            cout << "Edge Case "<< endl;
            if (h == 5) //top-edge
              set_space->up_ == nullptr;
            if (h == 0) // bottom-edge
              set_space->down_ == nullptr;
            if (v == 5) //right-side
              set_space->right_ == nullptr;
            if (v == 0) //left-side
              set_space->left_ == nullptr;
          }//of else
        }
      }
      cout << endl << endl << "Finished construction" << endl;
    }//of Grid constructor

    //ostream& display(ostream& out){
    void display(){
      //out << "Printing contents of row: ";
      cout << "Printing contents of row: ";
      for (auto elem : grid_) {
        //out << "Printing contents of row: ";
        cout << "Printing contents of row: ";
        for (int v = 0; v < v_columns_; v++) {
          Space *print_space;
          print_space = (elem[v]); 
          cout << print_space->v_index_ << ", " << print_space->h_index_ << endl;
          //out << print_space->v_index_ << ", " << print_space->h_index_ << endl;
        }
      }
      //return out;
    }//of display

};//of Grid

//used to set spaces and their pointers and owners at begining of match


int main(){
  long seed = 998765;
  default_random_engine dre(seed);
  cout << "Making grid in main...." << endl;
  Grid g; 
  cout << "Printing grid in main...." << endl;
  g.display();
  Die d; 

  cout << endl << "Rolling dice:" << endl;
  for (auto i = 0;i < 20; i++)
    d.roll(dre);
  return 0;


}//of main

