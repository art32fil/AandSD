#include <iostream>
#include <fstream>

using namespace std;

typedef struct Palindrome_Poistion {

  int start, end, length;
} PalPos ;


void checkForPalindrome (string & word, int &left, int &right, int couter) {

    
    cout << "   [";
    for (int i = 0; i <= couter; i++) 
        cout << "!";
   
    if (left > 0 && right < (int)word.length() && word[left - 1] == word[right + 1])
    {
        left--;
        right++;

        cout << "]  call  CP( ... , " << left << ", " << right << " ) --> [ ";
        for (int i = left; i <= right; i++) 
                cout << word[i];
        
        cout<< " ]\n";    
        checkForPalindrome (word, left, right, couter+1); 
    }
    else {

        cout << "]  call  CP( ... , " << left << ", " << right << " ) --> [ ";
            for (int i = left-1; i <= right+1; i++) 
                    cout << word[i];
            cout<< " ]\n";    
    }
    

    cout << "   [";
    for (int i = 0; i <= couter; i++) 
        cout << "!";
    cout << "]  end\n";


  return;
}


void LongestPalindrome (string &word, int index, PalPos &palindrome)
{
  if (index < (int)word.length() )
    {
        int left = index, right = index;
    
        if (word[left] == word[right + 1]){
            
            cout << "\n";
	        right++;
	        checkForPalindrome (word, left, right, 0);
        } 
        else {
            
            cout << "\n";
            checkForPalindrome (word, left, right, 0);
        }

        if (right - left > palindrome.length) {

	        palindrome.start = left;
	        palindrome.end = right;
	        palindrome.length = palindrome.end - palindrome.start;
	    }


        cout << "\n[";
        for (int i = 0; i <= index; i++)
            cout << "!";
        
        
        cout << "]  call  PL( ... , " 
             << index 
             <<", { "
             << palindrome.start 
             << ", " 
             << palindrome.end 
             << ", " 
             << palindrome.length 
             << "} )\n";

        LongestPalindrome (word, index+1, palindrome);    
    }

    cout << "[";
    for (int i = 0; i <= index; i++)
        cout << "!";
    
    cout << "]   end\n";
    return;
}


int main (int argc, char *argv[] ) {


    string input_word;
    PalPos palindrome;

    if( argc > 1 ) {

        ifstream input_file(argv[1]);
        ofstream output_file( argv[2] );

        while (input_file >> input_word){

            cout << "\n[=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=]\n|\t\t"
                << input_word         
                <<"\n[=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=]\n";
            palindrome = { 0, 0, 0 };

             
            
            LongestPalindrome (input_word, 0, palindrome);

            if( palindrome.length >1 ) {

                output_file << input_word << " ["<< palindrome.start << ":" << palindrome.end <<"] ---> "; 
                cout <<"\n[ Result ]\n\n    "<< input_word << " ["<< palindrome.start << ":" << palindrome.end <<"] ---> "; 
                for (int i = 0; i < palindrome.start; i++) 
                {
                    output_file << input_word[i];
                    cout << input_word[i];
                }
                output_file <<"|"; 
                cout <<"|"; 
                for (int i =palindrome.start; i <= palindrome.end; i++ ) {

                    output_file << input_word[i];
                    cout << input_word[i];
                }
                
                output_file <<"|"; 
                cout <<"|"; 
                
                for (int i = palindrome.end+1; i < (int)input_word.length(); i++) 
                {
                    output_file << input_word[i];
                    cout << input_word[i];
                }
                output_file << "\n\n";
                cout << "\n\n[ Search completed ]\n\n";
            }
            else
            {
                output_file << input_word << " [-:-] ---> Palindrome not found!!!\n\n";
                cout << input_word << " [-:-] ---> Palindrome not found !!!\n\n";
            }
        }
        output_file.close();
        input_file.close();
    }
    else
    {
       palindrome = { 0, 0, 0 };
        cin >> input_word;
        
        LongestPalindrome (input_word, 0, palindrome);

            for (int i =palindrome.start; i <=palindrome.end; i++) 
            {
                cout << input_word[i];
            }
            cout << "\n";
    }
    
    cout << "[ Prosses Finshed ] \n> Goodbye!\n";
  return 0;
}
