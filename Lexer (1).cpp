#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
 
using namespace std;
ifstream file("program.txt");		// File to get Code
ofstream file2("tokens.txt");		// File to get Result as Tokens
 
bool isKeyword(char buffer[]){
	char keywords[35][10] = {"main","auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while","cout" , "cin"};
	int i;
	bool flag = false;
	for(i = 0; i < 35; ++i){
		if(strcmp(keywords[i], buffer) == false){
			flag = true;
			break;
		}
	}
	return flag;
}

bool isNumber(char buffer[]){
	for(int i = 0; buffer[i] != '\0'; i++){
		if(buffer[i] == '.'){
			continue;
		}
		if(isdigit(buffer[i]) == false)
    	return false;
    }
    return true;
}

bool checkNumber(char buffer[]){
	for(int i = 0; buffer[i] != '\0'; i++)
		if(isdigit(buffer[i]) == true)
    	return true;
    return false;
}

void displayError(char buffer[]){
	cout << buffer << " \t\tis a wrong Letter in the Code\n";
   	file2 << buffer << " \t\tis a wrong Letter in the Code\n";
}

bool isIdentifier(char buffer[]){
	if(buffer[0] != '@'){
		return false;
	}
	if(isdigit(buffer[1]) == 1){
		return false;
	}
	if(checkNumber(buffer) == 0){
		return false;
	}
	return true;
}
 
int main(){
	char ch, buffer[15];
	char operators[] = {'+','-','*','/','%','=','<','>'};
	char punctuations[] = {',',';','[','{','(',')','}',']'};
	int i, j=0;
	
	if(!file.is_open()){
		cout<<"error while opening the file\n";
		exit(0);
	}
	
	if(!file2.is_open()){
		cout<<"error while opening the file\n";
		exit(0);
	}
	
	while(!file.eof()){
   		ch = file.get();
   		
		for(i = 0; i < 8; ++i){		// Code to Check Operaters
   			if(ch == operators[i]){
   				if(ch == '='){
   					cout << ch << " \t\tis an assignment Operator\n";
   					file2 << ch << " \t\tis an assignment Operator\n";
				   }
				else{
					cout << ch << " \t\tis an Operator\n";
   					file2 << ch << " \t\tis an Operator\n";	
				}
   			}
   		}
   		
   		for(i = 0; i < 7; ++i){		// Code to check Punctuations
   			if(ch == punctuations[i]){
   				cout << ch << " \t\tis a Punctuation\n";
   				file2 << ch << " \t\tis a Punctuation\n";
   			}
		}
   		if(ch == '@'){
   			buffer[j++] = ch;
		}
   		else if(isalnum(ch) || ch == '.'){
   			buffer[j++] = ch;
   		}
   		else if((ch == ' ' || ch == '\n') && (j != 0)){
   			buffer[j] = '\0';
   			j = 0;
   			
   			if(isKeyword(buffer) == 1){
				cout << buffer << " \t\tis a Keyword\n";
   				file2 << buffer << " \t\tis a Keyword\n";
			   }
   			else if(isNumber(buffer)){
   				cout << buffer << " \t\tis a Number\n";
   				file2 << buffer << " \t\tis a Number\n";
   			}
   			else if(isIdentifier(buffer)){
   				cout << buffer << " \t\tis an Identifier\n";
   				file2 << buffer << " \t\tis an Identifier\n";
			}
			else
			displayError(buffer);
			buffer[0] = '\0';
		}
	}
	file.close();
	file2.close();
	return 0;
}



