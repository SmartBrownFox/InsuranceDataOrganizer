// Programmer: Wesley Charlton
// Purpose: This program reads insurance client data from a file, processes it, and then generates various reports (such as)
// client lists, lotal clients, policy info, etc.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Function prototypes
void fillVectors(vector<string>& clientName, vector<string>& policy,
                 vector<int>& yrs, vector<double>& premium, int& numClients);
void printVectors(const vector<string>& clientName, const vector<string>& policy,
                  const vector<int>& yrs, const vector<double>& premium, int numClients);
void selSort(vector<string>& clientName, vector<string>& policy,
             vector<int>& yrs, vector<double>& premium, int numClients);
void loyalClient(const vector<string>& clientName, const vector<int>& yrs, int numClients);
void showBoats(const vector<string>& clientName, const vector<string>& policy,
               const vector<double>& premium, int numClients);
int highestPremium(const vector<double>& premium, int numClients);
int binarySearch(const vector<string>& clientName, int numClients, string keyName);
void findClient(const vector<string>& clientName, const vector<string>& policy,
                const vector<int>& yrs, const vector<double>& premium, int numClients);

int main() {
	// Declare vectors with fixed size of 50
	vector<string> clientName(50);
	vector<string> policy(50);
	vector<int> yrs(50);
	vector<double> premium(50);
	int numClients = 0; // Actual number of clients read

	// Read data from file into vectors
	fillVectors(clientName, policy, yrs, premium, numClients);

	// Display original data
	cout << "************************************************************" << endl;
	printVectors(clientName, policy, yrs, premium, numClients);

	// Sort data by client name
	selSort(clientName, policy, yrs, premium, numClients);

	// Display sorted data
	cout << "************************************************************" << endl;
	printVectors(clientName, policy, yrs, premium, numClients);

	// Display loyal clients (10+ years)
	cout << "Loyal Client List:" << endl;
	cout << "------------------------------------------------------------" << endl;
	loyalClient(clientName, yrs, numClients);

	// Display boat policies with high premiums
	cout << "************************************************************" << endl;
	cout << "Show Boat List:" << endl;
	cout << "------------------------------------------------------------" << endl;
	showBoats(clientName, policy, premium, numClients);

	// Find and display client with highest premium
	int highestIndex = highestPremium(premium, numClients);
	cout << "************************************************************" << endl;
	cout << clientName[highestIndex] << " has the highest premium of $ "
	     << premium[highestIndex] << endl;

	// Searches for a specific client + their info
	findClient(clientName, policy, yrs, premium, numClients);

	return 0;
}

// Reads data from file into vectors
void fillVectors(vector<string>& clientName, vector<string>& policy,
                 vector<int>& yrs, vector<double>& premium, int& numClients) {
	ifstream inFile("insur.txt");

	// Check if file opened successfully
	if (!inFile) {
		cout << "Error opening file. Program terminating." << endl;
		exit(1);
	}

	// Read data until EOF or vector is full
	numClients = 0;
	while (numClients < 50 && getline(inFile, clientName[numClients])) {
		getline(inFile, policy[numClients]);
		inFile >> yrs[numClients];
		inFile >> premium[numClients];
		inFile.ignore(); // Clear newline character
		numClients++;
	}

	inFile.close();
}

// Prints all client data in tabular format
void printVectors(const vector<string>& clientName, const vector<string>& policy,
                  const vector<int>& yrs, const vector<double>& premium, int numClients) {
	// Table headers
	cout << setw(20) << left << "client"
	     << setw(10) << left << "policy"
	     << setw(5) << right << "yrs"
	     << setw(10) << right << "prem" << endl;

	cout << setw(20) << left << "-------------------"
	     << setw(10) << left << "----------"
	     << setw(5) << right << "----"
	     << setw(10) << right << "----------" << endl;

	// Table data
	for (int i = 0; i < numClients; i++) {
		cout << setw(20) << left << clientName[i]
		     << setw(10) << left << policy[i]
		     << setw(5) << right << yrs[i]
		     << setw(10) << right << premium[i] << endl;
	}
}

// Sorts all vectors by client name using selection sort
void selSort(vector<string>& clientName, vector<string>& policy,
             vector<int>& yrs, vector<double>& premium, int numClients) {
	int minIndex;
	string minValue;

	for (int start = 0; start < numClients - 1; start++) {
		minIndex = start;
		minValue = clientName[start];

		for (int index = start + 1; index < numClients; index++) {
			if (clientName[index] < minValue) {
				minValue = clientName[index];
				minIndex = index;
			}
		}

		// Swap client names
		swap(clientName[minIndex], clientName[start]);
		// Swap policies
		swap(policy[minIndex], policy[start]);
		// Swap years
		swap(yrs[minIndex], yrs[start]);
		// Swap premiums
		swap(premium[minIndex], premium[start]);
	}
}

// Displays clients with 10 or more years of service
void loyalClient(const vector<string>& clientName, const vector<int>& yrs, int numClients) {
	for (int i = 0; i < numClients; i++) {
		if (yrs[i] >= 10) {
			cout << clientName[i] << " " << yrs[i] << endl;
		}
	}
}

// Displays boat policies with premiums of $4800 or more
void showBoats(const vector<string>& clientName, const vector<string>& policy,
               const vector<double>& premium, int numClients) {
	for (int i = 0; i < numClients; i++) {
		if (policy[i] == "Boat" && premium[i] >= 4800) {
			cout << clientName[i] << " " << policy[i] << " " << premium[i] << endl;
		}
	}
}

// Returns the index of the client with the highest premium
int highestPremium(const vector<double>& premium, int numClients) {
	int highestIndex = 0;

	for (int i = 1; i < numClients; i++) {
		if (premium[i] > premium[highestIndex]) {
			highestIndex = i;
		}
	}

	return highestIndex;
}

// Binary search for a client by name
int binarySearch(const vector<string>& clientName, int numClients, string keyName) {
	int first = 0, last = numClients - 1, middle;

	while (first <= last) {
		middle = (first + last) / 2;

		if (clientName[middle] == keyName) {
			return middle; // Found
		} else if (clientName[middle] > keyName) {
			last = middle - 1;
		} else {
			first = middle + 1;
		}
	}

	return -1; // Not found
}

// Prompts user for a client name and displays their information
void findClient(const vector<string>& clientName, const vector<string>& policy,
                const vector<int>& yrs, const vector<double>& premium, int numClients) {
	string searchName;

	cout << "************************************************************" << endl;
	cout << "Enter the client's name: ";
	getline(cin, searchName);

	int position = binarySearch(clientName, numClients, searchName);

	if (position == -1) {
		cout << "Client not found." << endl;
	} else {
		cout << "Client: " << clientName[position] << endl;
		cout << "Policy: " << policy[position] << endl;
		cout << "Years: " << yrs[position] << endl;
		cout << "Premium: " << premium[position] << endl;
	}
}