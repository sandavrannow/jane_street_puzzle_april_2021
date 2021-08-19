#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std ;

struct Node {
    //

    Node * left_node ;
    Node * right_node ;
    bool is_leaf ;
    double leaf_left ;
    double leaf_right ;


    // INITIALIZE A NON LEAF NODE WITH THIS METHOD
    Node( Node * left_node_in , Node * right_node_in )  ;

    // INIITIALIZE A LEAF NODE WITH THIS METHOD
    Node( double leaf_left_in , double leaf_right_in ) ;

};

Node::Node( Node * left_node_in , Node * right_node_in ) {
    //
    left_node = left_node_in ;
    right_node = right_node_in ;
    is_leaf = false ;
    leaf_left = 0 ;
    leaf_right = 0 ;
}

Node::Node( double leaf_left_in , double leaf_right_in ) {
    //
    left_node = nullptr ;
    right_node = nullptr ;
    is_leaf = true ;
    leaf_left = leaf_left_in ;
    leaf_right = leaf_right_in ;

}

struct Puzzle {

    vector<Node> node_vector ;

    void add_normal_node(  Node * left_node_in , Node * right_node_in ) ;
    void add_leaf_node( int leaf_left_in , int leaf_right_in ) ;


    vector<vector<double>> solve_puzzle() ;
    vector<vector<double>> calculate_method( Node * node_in ) ;
    Puzzle( bool pre_swap ) ;

    Node * node_one ;
    Node * node_two ;
    Node * node_three ;
    Node * node_four ;
    Node * node_five ;
    Node * node_six ;
    Node * node_seven ;
    Node * node_eight ;
    Node * node_nine ;
    Node * node_ten ;
    Node * node_eleven ;
    Node * node_twelve ;
    Node * node_thirteen ;
    Node * node_fourteen ;
    Node * node_fifteen ;

};

Puzzle::Puzzle( bool pre_swap ) {
    //

    if ( pre_swap == true ) {

        // INITIALIZE THE VALUES AND NODES THE ORIGINAL WAY

        node_one = new Node( 1.0 , 16.0 ) ;
        node_two = new Node( 8.0 , 9.0 ) ;
        node_three = new Node( 5.0 , 12.0 ) ;
        node_four = new Node( 4.0 , 13.0 ) ;
        node_five = new Node( 6.0 , 11.0 ) ;
        node_six = new Node( 3.0 , 14.0 ) ;
        node_seven = new Node( 7.0 , 10.0 ) ;
        node_eight = new Node( 2.0 , 15.0 ) ;

        // WHEN MAKING A NORMAL NODE PASS A POINTER TO THE NODE BECAUSE WE NEED TO USE POINTERS

        node_nine = new Node( node_one , node_two ) ;
        node_ten = new Node( node_three , node_four ) ;
        node_eleven = new Node( node_five , node_six ) ;
        node_twelve = new Node( node_seven , node_eight ) ;
        node_thirteen = new Node( node_nine , node_ten ) ;
        node_fourteen = new Node( node_eleven , node_twelve ) ;
        node_fifteen = new Node( node_thirteen , node_fourteen ) ;

    }
    else {
        // INITIALIZE THE VALUES AND NODES THE ORIGINAL WAY EXCEPT CHANGE SEED 3 AND SEED 16 - > HANDLE THIS AFTER WE FINISH THE ORIGINAL ONE

        // INITIALIZE THE VALUES AND NODES THE ORIGINAL WAY


        node_one = new Node( 1.0 , 3.0 ) ;
        node_two = new Node( 8.0 , 9.0 ) ;
        node_three = new Node( 5.0 , 12.0 ) ;
        node_four = new Node( 4.0 , 13.0 ) ;
        node_five = new Node( 6.0 , 11.0 ) ;
        node_six = new Node( 16.0 , 14.0 ) ;
        node_seven = new Node( 7.0 , 10.0 ) ;
        node_eight = new Node( 2.0 , 15.0 ) ;

        // WHEN MAKING A NORMAL NODE PASS A POINTER TO THE NODE BECAUSE WE NEED TO USE POINTERS

        node_nine = new Node( node_one , node_two ) ;
        node_ten = new Node( node_three , node_four ) ;
        node_eleven = new Node( node_five , node_six ) ;
        node_twelve = new Node( node_seven , node_eight ) ;
        node_thirteen = new Node( node_nine , node_ten ) ;
        node_fourteen = new Node( node_eleven , node_twelve ) ;
        node_fifteen = new Node( node_thirteen , node_fourteen ) ;

    }
}

vector<vector<double>> Puzzle::solve_puzzle() {
    //

    vector<vector<double>> results_matrix = calculate_method( node_fifteen ) ;
    for ( vector<double> pair : results_matrix ) {
        //
        cout << " Node Id : " << pair[ 0 ] << " Node Possibility Of Winning The Whole Thing " << pair[ 1 ] << endl ;
    }
    return results_matrix ;
}

vector<vector<double>> Puzzle::calculate_method( Node * node_in ) {
    //

    if ( node_in->is_leaf == true ) {
        // BASE CASE IF WE ARE ON THE ROOT JUST ABOVE THE NUMBERS - > SO RETURN A LIST OF LIST CONTAINING [ NUMBER ID , NUMBER POSSIBILITY ]

        // POSSIBILITY OF LEFT ADVANCING TO THE NEXT STAGE
        double poss_left = ( node_in->leaf_right ) / ( node_in->leaf_left + node_in->leaf_right ) ;

        // POSSIBILITY OF RIGHT ADVANCING TO THE NEXT STAGE


        double poss_right = ( node_in->leaf_left ) / ( node_in->leaf_left + node_in->leaf_right ) ;

        vector<vector<double>> return_vector = {} ;

        vector<double> left_vector = { ( double ) node_in->leaf_left , ( double ) poss_left } ;
        vector<double> right_vector = { ( double ) node_in->leaf_right , ( double ) poss_right } ;

        return_vector.push_back( left_vector ) ;
        return_vector.push_back( right_vector ) ;

        return return_vector ;

    }
    else {

        // IF WE ARE IN THE MIDDLE NODES OR AT THE TOP NODE WE FIRST NEED TO RECURSE TO BOTH THE LEFT SUBTREE AND THE RIGHT SUB TREE

        vector<vector<double>> left_results = calculate_method( node_in->left_node ) ;

        vector<vector<double>> right_results = calculate_method( node_in->right_node ) ;

        unordered_map<double,double> hash_map_results = {} ; // BE CAREFUL

        // { NODE ID : [ PARTIAL POSSIBILITIES THAT SOMEONE CAN GO TO THE NEXT STAGE ] } - > { NODE ID : SUM POSSIBILITY THAT SOMEONE CAN GO TO THE NEXT STAGE }
        for ( vector<double> left_pair : left_results ) {
            for ( vector<double> right_pair : right_results ) {

                // ADD TO THEIR RESPECTIVE IDS AND MAKE SURE THE HASH MAP WORKS

                if ( ! hash_map_results.contains( left_pair[ 0 ] ) ) {
                    //
                    hash_map_results[ left_pair[ 0 ] ] = ( ( right_pair[ 0 ] /  ( left_pair[ 0 ] + right_pair[ 0 ] ) ) * ( left_pair [ 1 ] * right_pair[ 1 ] ) ) ;
                }
                else {
                    //
                    hash_map_results[ left_pair[ 0 ] ] += ( ( right_pair[ 0 ] /  ( left_pair[ 0 ] + right_pair[ 0 ] ) ) * ( left_pair [ 1 ] * right_pair[ 1 ] ) ) ;
                }
                if ( ! hash_map_results.contains( right_pair[ 0 ] ) ) {
                    //
                    hash_map_results[ right_pair[ 0 ] ] = ( ( left_pair[ 0 ] /  ( left_pair[ 0 ] + right_pair[ 0 ] ) ) * ( left_pair [ 1 ] * right_pair[ 1 ] ) ) ;

                }
                else {
                    //
                    hash_map_results[ right_pair[ 0 ] ] += ( ( left_pair[ 0 ] /  ( left_pair[ 0 ] + right_pair[ 0 ] ) ) * ( left_pair [ 1 ] * right_pair[ 1 ] ) ) ;
                }
            }
        }

        vector<vector<double>>  vector_results = {} ;

        // TRANSFORM THE HASH MAP INTO A LIST
        for ( pair<const double, double> now_pair : hash_map_results ) {
            vector<double> this_vector = { now_pair.first , now_pair.second } ;
            vector_results.push_back( this_vector ) ;
        }

        return vector_results ;
    }
}

int main() {

    cout << "Probability of each person or team winning the whole thing before the swap " << endl ;
    Puzzle pre_puzzle = Puzzle( true ) ;
    vector<vector<double>> pre_puzzle_probabilities = pre_puzzle.solve_puzzle() ;

    cout << "Probability of each person or team winning the whole thing after the swap " << endl ;
    Puzzle post_puzzle = Puzzle( false ) ;
    vector<vector<double>> post_puzzle_probabilities = post_puzzle.solve_puzzle() ;

    double pre_poss_two_winning_it_all = 0 ;
    for ( vector<double> now_vector : pre_puzzle_probabilities ) {
        if ( now_vector[ 0 ] == 2 ) {
            pre_poss_two_winning_it_all = now_vector[ 1 ] ;
        }
    }

    double post_poss_two_winning_it_all = 0 ;
    for ( vector<double> now_vector : post_puzzle_probabilities ) {
        if ( now_vector[ 0 ] == 2 ) {
            post_poss_two_winning_it_all = now_vector[ 1 ] ;
        }
    }

    double difference = post_poss_two_winning_it_all - pre_poss_two_winning_it_all ;
    cout << "The increase in probability of seed 2 winning the whole thing = " << difference << endl ;

}

