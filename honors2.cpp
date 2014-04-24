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

struct Player{
  public:
    vector<(Space*)> player_spaces_;
};//of Player

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

struct Grid{
  public:
    int h_rows_;
    int v_columns_;
    long total_spaces_;
    
    map< string, Space* > grid_coords_;

    ostream& display(ostream& out){
      out << "Trying to print" << endl;
      for (int h = h_rows_-1; h > -1; h--){
        for (int v = 0; v < v_columns_; v++){
          string h_str = to_string(h);
          string v_str = to_string(v);
          string coords = h_str+':'+v_str;
          auto map_itr = (grid_coords_.find(coords));
          out << map_itr->second->h_index_ << ':' << map_itr->second->v_index_ << ' ';
        }
        out << endl;
      }
      return out;
    }//of display

    Grid(int h_rows, int v_columns){
      h_rows_ = h_rows; v_columns_ = v_columns;
      total_spaces_ = (h_rows * v_columns);
      cout << "Making Grid: " << h_rows << ':' << v_columns << endl;
      for (int h = 0; h < h_rows_; h++){
        for (int v = 0; v < v_columns_; v++){
          string h_str = to_string(h);
          string v_str = to_string(v);
          string coords = h_str+':'+v_str;
          Space *set_space = (new Space(h, v));
          grid_coords_[coords] = set_space;

          if ((h != 0) && (h != 5) && (v != 5) && (v != 0)){
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
    }//of Grid
};//of Grid
//used to set spaces and their pointers and owners at begining of match

class Game{
  private:
    map<string, Space*> coords_left_;
    //the colomns and rows for space coordinates (0-5) ... think battleship
  public:
    Game(Grid &grid, default_random_engine &dre,Player &p1, Player &p2){
      coords_left_ = grid.grid_coords_;
      while(coords_left_.size() > (grid.total_spaces_/2))
      {
        auto it = coords_left_.begin();
        advance(it, rand() % coords_left_.size());
        Space* random_space = it->second;
        p1.player_spaces_.push_back(random_space); 
        coords_left_.erase(it->first);
      }//of for
      cout << endl;
      for (auto elem:coords_left_)
        cout << elem.first<< endl;
    }//of constructor
};//of GameBoard


int main(){
  long seed = 998765;
  default_random_engine dre(seed);
  Grid g(6,6);
  g.display(cout);
  Die d; 

  cout << endl << "Rolling dice:" << endl;
  for (auto i = 0;i < 20; i++)
    d.roll(dre);
  return 0;
}//of main

