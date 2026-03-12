#include <iostream>
#include <iomanip>  // Needed for fancy output stuff later
#include <string>

using namespace std;

int main() {
	// This makes a string with 10 stars. Much faster than typing "**********"
	string str0(10, '*');
	cout << "str0 = " << str0 << endl;

	string str1 = "Hello";
	auto str2 = "World"; // The compiler figures out the type here
	string str3 = str1 + " " + str2 + "!"; // Standard way to glue strings together
	
	// Tricky quotes and backslashes
	string str3a = "\"Hello \\ World!\""; 
	
	// Raw string - what you see is what you get! No need to escape backslashes
	auto str3b = R"("Hello \ world!")"; 

	cout << "str1:" << str1 << endl;
	cout << "str2:" << str2 << endl;
	cout << "str3:" << str3 << endl;
	cout << "str3a:" << str3a << endl;
	cout << "str3b:" << str3b << endl;

	// --- Checking size and space ---
	
	cout << "str3 capacity = " << str3.capacity() << endl; // How much memory is actually set aside
	cout << "str3 length(size) = " << str3.length() << endl; // How many letters are actually in it
	cout << "str3 max_size = " << str3.max_size() << endl; // The absolute legal limit for a string
	cout << "str3 size =" << str3.size() << endl; // Same as length
	cout << "str3 empty = " << str3.empty() << endl; // Returns 1 if it's empty, 0 if not

	// --- Grabbing specific characters ---
	
	cout << "str3[0] = " << str3[0] << endl; // Fast, but risky if string is empty
	cout << "str3.at(0) = " << str3.at(0) << endl; // Safer - tells you if you're trying to access a ghost character
	cout << "str3.at(4) = " << str3.at(4) << endl;
	cout << "str3.front() = " << str3.front() << endl; // Just the first one
	cout << "str3.back() = " << str3.back() << endl; // Just the last one

	// --- Taking a slice ---
	
	cout << "str3.substr(0, 5) = " << str3.substr(0, 5) << endl; // Hand me 5 characters starting at index 0
	cout << "str3.substr(7, 3) = " << str3.substr(7, 3) << endl; 

	// --- Adding stuff mid-way or at the end ---
	
	string str4;
	str4.append(str1);
	cout << "str4 = " << str4 << endl;
	str4.append(" ");
	str4 += str2; // Short version of append
	cout << "str4 = " << str4 << endl;
	str4.push_back('!'); // Plop a single character on the end
	cout << "str4 = " << str4 << endl;

	// --- Finding where names or letters are ---
	
	// Gives the index. If it fails, it returns a giant number (string::npos)
	cout << "str4.find(str1) = " << str4.find(str1) << endl;
	cout << "str4.find(\"World\", 3) = " << str4.find("World", 3) << endl; // Start looking from index 3
	cout << "str4.find(\"World\", 7) = " << str4.find("World", 7) << endl;

	// --- Changing the string content ---
	
	str4.insert(5, " C++"); // Jam this text in at position 5
	cout << "str4 = " << str4 << endl;
	
	// Delete a chunk in the middle
	str4.erase(str4.begin() + 6, str4.end() - 6);
	cout << "str4 = " << str4 << endl;
	
	str4.clear(); // Wipe everything out
	cout << "str4 = " << str4 << endl;


	// --- Changing strings into numbers ---
	
	string str5 = "1234567890";
	int number1 = stoi(str5); // "String to Int"
	cout << "number1 = " << number1 << endl;

	string str6 = "123.4567890";
	double number2 = stod(str6); // "String to Double" (for decimals)
	cout << "number2 = " << number2 << endl;


	// --- Changing numbers back into strings ---
	
	string str7 = to_string(number1);
	cout << "str7 = " << str7 << endl;

	string str8 = to_string(number2);
	cout << "str8 = " << str8 << endl;
}
