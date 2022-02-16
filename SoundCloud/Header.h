// Muhammad Shaheer
// 19I-2152
// Section-C
// Assignment-2

#pragma once
#include <iostream>
#include <fstream>
using namespace std;

// Declaring classes
template<typename T, typename U, typename V>
class MMD;

template<typename T, typename U, typename V = float>
class AMD;

template<typename T, typename U = string, typename V = float>
class Tracks;

template<typename T, typename U, typename V>
class AD;

template<typename T, typename U = string, typename V = float>
class Albums;

template<typename T, typename U = string, typename V = float>
class ADP;

//Music Metadata DataBase (A doubly linked list)
template<typename T, typename U, typename V>
class MMD
{
public:
	//data members
	T mbid{};
	U songName{};
	U writer{};
	V length{};
	AD<T, U, V>* album;

	//connections
	MMD<T, U, V>* next;
	MMD<T, U, V>* previous;

	MMD() {	// Default constructor
		next = previous = nullptr;
		album = nullptr;
	}

	void displayMMD() {	// Method to display data in MMD

		// Displaying MMD data
		cout << "******************************* BASIC MMD DATA *******************************" << endl;
		cout << "MBID: " << mbid << endl;
		cout << "Song name: " << songName << endl;
		cout << "Song writer: " << writer << endl;
		cout << "Song length: " << length << endl;

		// Displaying AD data of current MMD
		cout << "\n******************************* AD DATA OF MMD *******************************" << endl;
		cout << "ABID: " << album->abid << endl;
		cout << "Album name: " << album->albumName << endl;
		cout << "AID: " << album->aid << endl;
		cout << "Publisher: " << album->publisher << endl;
		cout << "Number of tracks: " << album->numberOfTracks << endl;
		cout << "Total duration: " << album->totalDuration << endl;

		// Displaying all tracks of AD of current MMD
		// Each track consist of MMD data which is not displayed
		cout << "\n******************************* TRACKS DATA OF AD OF MMD *******************************" << endl;

		Tracks<T>* tempTracks = album->tracks;

		while (tempTracks != nullptr) {
			cout << "Track no: " << tempTracks->trackNumber << endl;
			cout << "MBID: " << tempTracks->mbid << endl;
			tempTracks = tempTracks->next;
		}
	}
};

//Author Metadata DataBase (A circular linked list)
template<typename T, typename U, typename V = float>
class AMD
{
public:
	//data members
	T aid{};
	U authorName{};
	U band{};
	U gender{};
	T dateOfBirth{};
	T careerStartDate{};
	U genre{};
	AD<T, U, V>* albums;
	ADP<T>* adp;

	//connections
	AMD<T, U>* next;

	AMD() {	// Default constructor
		next = nullptr;
		albums = nullptr;
		adp = nullptr;
	}

	void displayAMD() {	// Method to display the data of AMD

		// Displaying AMD data
		cout << "******************************* BASIC AMD DATA *******************************" << endl;
		cout << "AID: " << aid << endl;
		cout << "Author name: " << authorName << endl;
		cout << "Band: " << band << endl;
		cout << "Gender: " << gender << endl;
		cout << "Date of birth: " << dateOfBirth << endl;
		cout << "Career start date: " << careerStartDate << endl;
		cout << "Genre: " << genre << endl;

		// Displaying AD data of AMD
		// Each AD consists all of its tracks which are not displayed
		cout << "\n******************************* AD DATA OF AMD *******************************" << endl;

		AD<T, U, V>* tempAD = albums;

		while (tempAD->next != albums) {
			cout << "ABID: " << tempAD->abid << endl;
			cout << "Album name: " << tempAD->albumName << endl;
			cout << "AID: " << tempAD->aid << endl;
			cout << "Publisher: " << tempAD->publisher << endl;
			cout << "Number of tracks: " << tempAD->numberOfTracks << endl;
			cout << "Total duration: " << tempAD->totalDuration << "\n\n";
			tempAD = tempAD->next;
		}

		cout << "ABID: " << tempAD->abid << endl;
		cout << "Album name: " << tempAD->albumName << endl;
		cout << "AID: " << tempAD->aid << endl;
		cout << "Publisher: " << tempAD->publisher << endl;
		cout << "Number of tracks: " << tempAD->numberOfTracks << endl;
		cout << "Total duration: " << tempAD->totalDuration << endl;
	}
};

//Tracks (A singly linked list)
template<typename T, typename U = string, typename V = float>
class Tracks
{
public:
	//data members
	T trackNumber{};
	T mbid{};
	MMD<T, U, V>* trackRef;

	//connections
	Tracks<T>* next;

	Tracks() {	// Default constructor
		next = nullptr;
		trackRef = nullptr;
	}
};

//Album DataBase (A circular linked list)
template<typename T, typename U, typename V>
class AD
{
public:
	//data members
	T abid{};
	U albumName{};
	T aid{};
	U publisher{};
	T numberOfTracks{};
	V totalDuration{};
	AMD<T, U>* author;
	Tracks<T>* tracks;
	ADP<T>* adp;

	//connections
	AD<T, U, V>* next;

	AD() {	// Default constructor
		next = nullptr;
		tracks = nullptr;
		author = nullptr;
		adp = nullptr;
	}

	void insertTrack(T newTrackNumber, T newMbid) {	// Method to insert a track in album

		// Creating and initializing a new MMD
		Tracks<T>* newTrack = new Tracks<T>();
		newTrack->trackNumber = newTrackNumber;
		newTrack->mbid = newMbid;

		// Developing a two way connection between AD and MMD
		MMD<T, U, V>* targetMMD = mmd;

		while (targetMMD != nullptr && targetMMD->mbid != newTrack->mbid) {
			targetMMD = targetMMD->next;
		}

		newTrack->trackRef = targetMMD;

		if (tracks == nullptr) {	// Inserting first track
			tracks = newTrack;
		}

		else {	// Inserting track after first track
			Tracks<T>* lastTrack = tracks;

			while (lastTrack->next != nullptr) {
				lastTrack = lastTrack->next;
			}

			lastTrack->next = newTrack;
		}
	}

	void displayTracks() {	// Method to display tracks of an album

		if (tracks == nullptr) {
			cout << "No tracks found!" << endl;
		}

		else {
			Tracks<T>* tempTracks = tracks;

			while (tempTracks != nullptr) {
				cout << "#########################" << endl;
				cout << "Track no: " << tempTracks->trackNumber << endl;
				cout << "MBID: " << tempTracks->mbid << "\n\n";
				cout << "MMD track ref data:\n\n";
				cout << "MBID: " << tempTracks->trackRef->mbid << endl;
				cout << "Song name: " << tempTracks->trackRef->songName << endl;
				cout << "Song writer: " << tempTracks->trackRef->writer << endl;
				cout << "Song length: " << tempTracks->trackRef->length << endl;
				cout << "#########################\n\n";
				tempTracks = tempTracks->next;
			}
		}
	}

	void displayAD() {	// Method to display the data of AD

		// Displaying AD data
		cout << "******************************* BASIC AD DATA *******************************" << endl;
		cout << "ABID: " << abid << endl;
		cout << "Album name: " << albumName << endl;
		cout << "AID: " << aid << endl;
		cout << "Publisher: " << publisher << endl;
		cout << "Number of tracks: " << numberOfTracks << endl;
		cout << "Total duration: " << totalDuration << endl;

		// Displaying AMD data of AD
		cout << "\n******************************* AMD DATA OF AD *******************************" << endl;
		cout << "AID: " << author->aid << endl;
		cout << "Author name: " << author->authorName << endl;
		cout << "Band: " << author->band << endl;
		cout << "Gender: " << author->gender << endl;
		cout << "Date of birth: " << author->dateOfBirth << endl;
		cout << "Career start date: " << author->careerStartDate << endl;
		cout << "Genre: " << author->genre << endl;

		// Displaying tracks of AD
		cout << "\n******************************* TRACKS DATA OF AD *******************************" << endl;
		displayTracks();
	}
};

//Albums (A singly linked list)
template<typename T, typename U = string, typename V = float>
class Albums
{
public:
	//data members
	T year{};
	T abid{};
	AD<T, U, V>* albumRef;

	//connections
	Albums<T>* next;

	Albums() {	// Default constructor
		next = nullptr;
		albumRef = nullptr;
	}
};

//Author Discography Playlist (A circular linked list)
template<typename T, typename U = string, typename V = float>
class ADP
{
public:
	//data members
	T did{};
	T aid{};
	AMD<T, U>* author;
	Albums<T, U, V>* albums;

	//connections
	ADP<T>* next;

	ADP() {	// Default constructor
		next = nullptr;
		albums = nullptr;
		author = nullptr;
	}

	void insertAlbum(T newAbid, T newYear) {	// Method to insert an album in ADP

		// Creating and initializing a new Album
		Albums<T, U, V>* newAlbum = new Albums<T, U, V>();
		newAlbum->abid = newAbid;
		newAlbum->year = newYear;

		// Developing a two way relationship ADP to AD
		AD<T, U, V>* targetAD = ad;

		while (targetAD->next != ad && targetAD->abid != newAlbum->abid) {
			targetAD = targetAD->next;
		}

		newAlbum->albumRef = targetAD;

		if (albums == nullptr) {	// Inserting first album
			albums = newAlbum;
		}

		else {	// Inserting album after first album
			Albums<T, U, V>* lastAlbum = albums;

			while (lastAlbum->next != nullptr) {
				lastAlbum = lastAlbum->next;
			}

			lastAlbum->next = newAlbum;
		}
	}

	void displayAlbums() {	// Method to display album in ADP

		if (albums == nullptr) {
			cout << "No albums found!" << endl;
		}

		else {
			Albums<T, U, V>* tempAlbum = albums;

			while (tempAlbum != nullptr) {
				cout << "#########################" << endl;
				cout << "ABID: " << tempAlbum->abid << endl;
				cout << "Year: " << tempAlbum->year << "\n\n";
				cout << "AD data of album ref:\n\n";
				cout << "ABID: " << tempAlbum->albumRef->abid << endl;
				cout << "Album name: " << tempAlbum->albumRef->albumName << endl;
				cout << "AID: " << tempAlbum->albumRef->aid << endl;
				cout << "Publisher: " << tempAlbum->albumRef->publisher << endl;
				cout << "Number of tracks: " << tempAlbum->albumRef->numberOfTracks << endl;
				cout << "Total duration: " << tempAlbum->albumRef->totalDuration << endl;
				cout << "#########################\n\n";
				tempAlbum = tempAlbum->next;
			}
		}
	}

	void displayADP() {	// Method to display ADP

		// Displaying ADP data
		cout << "******************************* BASIC ADP DATA *******************************" << endl;
		cout << "DID: " << did << endl;
		cout << "AID: " << aid << "\n\n";

		// Displaying Albums data of current ADP
		// AD of each album consists of tracks and AMD data which is not displayed
		displayAlbums();
	}
};

// Node class
template<typename T>
class Node {

public:
	T data{};
	Node<T>* next;
	Node() { next = nullptr; }	// Default constructor
};

// Queue class
template<typename T>
class Queue {

private:
	Node<T>* front;
	Node<T>* rear;

public:
	Queue() { front = rear = nullptr; }	// Default constructor
	bool isEmpty() { return front == nullptr && rear == nullptr; }	// Method to check is queue is empty or not

	void enQueue(T newData) {	// Method to insert in queue

		// Creating and initializing new node
		Node<T>* newNode = new Node<T>();
		newNode->data = newData;

		if (isEmpty()) {	// If queue is empty
			front = rear = newNode;
		}

		else {	// If queue is not empty
			rear->next = newNode;
			rear = newNode;
		}
	}

	void deQueue() {	// Method to delete from queue (Can be modified to return data of deleted node)

		if (isEmpty()) {	// If queue is empty
			cout << "Queue is empty!" << endl;
		}

		else {	// If queue is not empty
			Node<T>* targetNode = front;
			front = front->next;
			if (front == nullptr) { rear = nullptr; }	// If last left element is deleted
			delete targetNode;
		}
	}

	Node<T>* getFront() {
		return front;
	}

	void display() {	// Method to display the queue

		if (isEmpty()) {	// If queue is empty
			cout << "Queue is empty!" << endl;
		}

		else {	// If queue is not empty
			Node<T>* tempNode = front;

			while (tempNode != nullptr) {
				cout << tempNode->data << endl;
				tempNode = tempNode->next;
			}
		}
	}
};

// Method to insert in sorted order in MMD double linked list
template<typename T, typename U, typename V>
void insertSortedMMD(MMD<T, U, V>*& head, MMD<T, U, V>* newMMD) {

	if (head == nullptr) {	// Inserting first MMD
		head = newMMD;
	}

	else if (head->mbid >= newMMD->mbid) {	// If MMD is to be inserted at head
		newMMD->next = head;
		head->previous = newMMD;
		head = newMMD;
	}

	else {	// If MMD is to be inserted after head
		MMD<T, U, V>* targetMMD = head;

		while (targetMMD->next != nullptr && targetMMD->next->mbid < newMMD->mbid) {
			targetMMD = targetMMD->next;
		}

		if (targetMMD->next != nullptr) {	// If MMD is to be inserted in between
			newMMD->next = targetMMD->next;
			newMMD->previous = targetMMD;
			targetMMD->next->previous = newMMD;
			targetMMD->next = newMMD;
		}

		else {	// If MMD is to be inserted at end
			targetMMD->next = newMMD;
			newMMD->previous = targetMMD;
		}
	}
}

// Method to insert in sorted order in AMD circular linked list
template<typename T, typename U, typename V = float>
void insertSortedAMD(AMD<T, U>*& head, AMD<T, U>* newAMD) {

	if (head == nullptr) {	// Inserting first AMD 
		newAMD->next = newAMD;
		head = newAMD;
	}

	else if (head->aid >= newAMD->aid) {	// If new AMD is to be inserted at head
		AMD<T, U>* lastAMD = head;

		while (lastAMD->next != head) {
			lastAMD = lastAMD->next;
		}

		newAMD->next = head;
		head = newAMD;
		lastAMD->next = head;
	}

	else {	// If new AMD is to be inserted after head
		AMD<T, U>* targetAMD = head;

		while (targetAMD->next != head && targetAMD->next->aid < newAMD->aid) {
			targetAMD = targetAMD->next;
		}

		newAMD->next = targetAMD->next;
		targetAMD->next = newAMD;
	}
}

// Method to insert in sorted order in AD circular linked list
template<typename T, typename U, typename V>
void insertSortedAD(AD<T, U, V>*& head, AD<T, U, V>* newAD) {

	if (head == nullptr) {	// Inserting first AD
		newAD->next = newAD;
		head = newAD;
	}

	else if (head->abid >= newAD->abid) {	// If new AD is to be inserted at head
		AD<T, U, V>* lastAD = head;

		while (lastAD->next != head) {
			lastAD = lastAD->next;
		}

		newAD->next = head;
		head = newAD;
		lastAD->next = head;
	}

	else {	// If new AD is to be inserted after head
		AD<T, U, V>* targetAD = head;

		while (targetAD->next != head && targetAD->next->abid < newAD->abid) {
			targetAD = targetAD->next;
		}

		newAD->next = targetAD->next;
		targetAD->next = newAD;
	}
}

// Method to insert AD in MMD (Two way relationship between AD and MMD)
template<typename T, typename U, typename V>
void insertADInMMD(AD<T, U, V>* newAD, T mbidNumber) {

	// Developing two way relationship between AD and MMD
	MMD<T, U, V>* targetMMD = mmd;

	while (targetMMD != nullptr && targetMMD->mbid != mbidNumber) {
		targetMMD = targetMMD->next;
	}

	if (targetMMD != nullptr) {
		targetMMD->album = newAD;
	}
}

// Method to insert AD in AMD (Two way relationship between AD and AMD)
template<typename T, typename U, typename V>
void insertADInAMD(AD<T, U, V>* newAD, AD<T, U, V>* amdAD) {

	// Developing a two way relationship between AD and AMD
	AMD<T, U>* targetAMD = amd;

	while (targetAMD->next != amd && targetAMD->aid != amdAD->aid) {	// Locating target AMD
		targetAMD = targetAMD->next;
	}

	// Saving target AMD (Author) in new AD's
	newAD->author = targetAMD;
	amdAD->author = targetAMD;

	// Inserting current AD (Album) in respective AMD
	if (targetAMD->albums == nullptr) {
		amdAD->next = amdAD;
		targetAMD->albums = amdAD;
	}

	else {
		AD<T, U, V>* lastAlbum = targetAMD->albums;

		while (lastAlbum->next != targetAMD->albums) {
			lastAlbum = lastAlbum->next;
		}

		amdAD->next = targetAMD->albums;
		lastAlbum->next = amdAD;
	}
}

// Method to insert in sorted order in ADP circular linked list
template<typename T, typename U = string, typename V = float>
void insertSortedADP(ADP<T>*& head, ADP<T>* newADP) {

	if (head == nullptr) {	// Inserting first ADP
		newADP->next = newADP;
		head = newADP;
	}

	else if (head->did >= newADP->did) {	// If new ADP is to be inserted at head
		ADP<T>* lastADP = head;

		while (lastADP->next != head) {
			lastADP = lastADP->next;
		}

		newADP->next = head;
		head = newADP;
		lastADP->next = head;
	}

	else {	// If new ADP is to be inserted after head
		ADP<T>* targetADP = head;

		while (targetADP->next != head && targetADP->next->did < newADP->did) {
			targetADP = targetADP->next;
		}

		newADP->next = targetADP->next;
		targetADP->next = newADP;
	}
}

// Method to insert ADP in AD (Two way relationship between ADP and AMD)
template<typename T, typename U = string, typename V = float>
void insertADPInAD(ADP<T>* newADP, T abidNumber) {

	// Developing a two way relationship AD to ADP
	AD<T, U, V>* targetAD = ad;

	while (targetAD->next != ad && targetAD->abid != abidNumber) {
		targetAD = targetAD->next;
	}

	targetAD->adp = newADP;
}

// Method to insert ADP in AMD (Two way relationship between ADP and AMD)
template<typename T, typename U = string, typename V = float>
void insertADPInAMD(ADP<T>* newADP, ADP<T>* amdADP) {

	// Developing a two way relationship between ADP and AMD
	AMD<T, U>* targetAMD = amd;

	while (targetAMD->next != amd && targetAMD->aid != amdADP->aid) {	// Locating target AMD
		targetAMD = targetAMD->next;
	}

	// Saving target AMD (Author) in new ADP's
	newADP->author = targetAMD;
	amdADP->author = targetAMD;

	// Inserting current ADP in respective AMD
	if (targetAMD->adp == nullptr) {
		amdADP->next = amdADP;
		targetAMD->adp = amdADP;
	}

	else {
		ADP<T>* lastADP = targetAMD->adp;

		while (lastADP->next != targetAMD->adp) {
			lastADP = lastADP->next;
		}

		amdADP->next = targetAMD->adp;
		lastADP->next = amdADP;
	}
}

//Functions Prototypes
template<typename T, typename U, typename V>
MMD<T, U, V>* Create_MMD(string path) //should return head of the MMD linkedlist
{
	ifstream ifile;	// Creating file reading object

	ifile.open(path);	// Opening file

	if (ifile) {	// If file is opened successfully
		string input = "";
		Queue<string> queue;
		MMD<T, U, V>* head = nullptr;	// Creating MMD head

		getline(ifile, input);	// Skipping first line in file

		while (getline(ifile, input)) {	// Reading data from file into the queue
			queue.enQueue(input);
		}

		while (!queue.isEmpty()) {
			input = queue.getFront()->data; queue.deQueue();	// Getting data from queue (FIFO)
			int commaCount = 0;
			MMD<T, U, V>* newMMD = new MMD<T, U, V>();	// Creating new MMD
			T mbidNumber{};

			for (int i = 0; input[i] != ','; i++) {	// Tokenizing and storing mbid number
				mbidNumber = (mbidNumber * 10) + (input[i] - 48);
			}

			newMMD->mbid = mbidNumber;	// Setting mbid number of new MMD

			// Saving information from file
			for (int i = 0; input[i] != '\0'; i++) {

				if (input[i] == ',') {	// If comma if reached
					commaCount = commaCount + 1;

					if (commaCount == 1) {	// Tokenizing and storing song name
						string songName = "";

						for (int j = i + 1; input[j] != ','; j++) {
							songName = songName + input[j];
						}

						if (mbidNumber == 100) {	// Song name with mbid 100 is comma seperated
							songName = "\"Blood, Tears, Dust\"";
						}

						newMMD->songName = songName;	// Setting song name of new MMD
					}

					else if (commaCount == 2) {	// Tokenizing and storing writer name
						string writerName = "";

						for (int j = i + 1; input[j] != ','; j++) {
							writerName = writerName + input[j];
						}

						if (mbidNumber == 100) {	// Song name with mbid 100 is comma seperated
							writerName = "Madonna";
						}

						newMMD->writer = writerName;	// Setting writer name of new MMD
					}

					else if (commaCount == 3) {	// Tokenizing and storing song length
						string songLength = "";

						for (int j = i + 1; input[j] != '\0'; j++) {
							songLength = songLength + input[j];
						}

						if (mbidNumber == 100) {	// Song name with mbid 100 is comma seperated
							songLength = "3.55";
						}

						newMMD->length = stod(songLength);	// Setting song length of new MMD
					}
				}
			}

			insertSortedMMD<T, U, V>(head, newMMD);	// Sorted insertion in MMD double linked list
		}

		ifile.close();	// Closing file

		return head;
	}

	else {	// If file does not opens successfully
		cout << "Error opening file ..." << endl;
		return nullptr;
	}
}

template<typename T, typename U, typename V = float>
AMD<T, U>* Create_AMD(string path) //should return head of the AMD linkedlist
{
	ifstream ifile;	// Creating file reading object

	ifile.open(path);	// Opening file

	if (ifile) {	// If file is opened successfully
		string input = "";
		Queue<string> queue;
		AMD<T, U>* head = nullptr;	// Creating AMD head

		getline(ifile, input);	// Skipping first line in file

		while (getline(ifile, input)) {	// Reading data from file into the queue
			queue.enQueue(input);
		}

		while (!queue.isEmpty()) {
			input = queue.getFront()->data; queue.deQueue();	// Getting data from queue (FIFO)
			int commaCount = 0;
			AMD<T, U>* newAMD = new AMD<T, U>();
			T aidNumber{};

			for (int i = 0; input[i] != ','; i++) {	// Tokenizing and storing aid number
				aidNumber = (aidNumber * 10) + (input[i] - 48);
			}

			newAMD->aid = aidNumber;	// Setting aid number of new AMD

			// Saving information from file
			for (int i = 0; input[i] != '\0'; i++) {

				if (input[i] == ',') {	// If comma if reached
					commaCount = commaCount + 1;

					if (commaCount == 1) {	// Tokenizing and storing author name
						string authorName = "";

						for (int j = i + 1; input[j] != ','; j++) {
							authorName = authorName + input[j];
						}

						newAMD->authorName = authorName;	// Setting author name of new AMD
					}

					else if (commaCount == 2) {	// Tokenizing and storing band
						string bandName = "";

						for (int j = i + 1; input[j] != ','; j++) {
							bandName = bandName + input[j];
						}

						newAMD->band = bandName;	// Setting band of AMD
					}

					else if (commaCount == 3) {	// Tokenizing and storing gender
						string gender = "";

						for (int j = i + 1; input[j] != ','; j++) {
							gender = gender + input[j];
						}

						newAMD->gender = gender;	// Setting gender of new AMD
					}

					else if (commaCount == 4) {	// Tokenizing and storing date of birth
						string dateBirth = "";

						for (int j = i + 1; input[j] != ','; j++) {
							dateBirth = dateBirth + input[j];
						}

						newAMD->dateOfBirth = stoi(dateBirth);	// Setting date of birth of new AMD
					}

					else if (commaCount == 5) {	// Tokenizing and storing career start date
						string careerDate = "";

						for (int j = i + 1; input[j] != ','; j++) {
							careerDate = careerDate + input[j];
						}

						newAMD->careerStartDate = stoi(careerDate);	// Setting career start date of new AMD
					}

					else if (commaCount == 6) {	// Tokenizing and storing genre
						string genre = "";

						for (int j = i + 1; input[j] != '\0'; j++) {
							genre = genre + input[j];
						}

						newAMD->genre = genre;	// Setting genre of new AMD
					}
				}
			}

			insertSortedAMD<T, U>(head, newAMD);	// Sorted insertion in AMD circular linked list
		}

		ifile.close();	// Closing file

		return head;
	}

	else {	// If file does not opens successfully
		cout << "Error opening file ..." << endl;
		return nullptr;
	}
}

template <typename T, typename U, typename V>
AD<T, U, V>* Create_AD(string path) //should return head of the AD linkedlist
{
	// Good way
	ifstream ifile;	// Creating file reading object

	ifile.open(path);	// Opening file

	if (ifile) {	// If file is opened successfully
		string input = "";
		Queue<string> queue;
		AD<T, U, V>* head = nullptr;	// Creating AD head
		T previousAbid{};
		bool infoSaved = false;	// To save information other than track just once in AD

		getline(ifile, input);	// Skipping first line in file

		while (getline(ifile, input)) {	// Reading data from file into the queue
			queue.enQueue(input);
		}

		AD<T, U, V>* newAD = new AD<T, U, V>();	// Creating a new AD
		AD<T, U, V>* amdAD = new AD<T, U, V>();	// Creating a new AD to add in AMD

		while (!queue.isEmpty()) {
			input = queue.getFront()->data; queue.deQueue();	// Getting data from queue (FIFO)
			int commaCount = 0;
			T abidNumber{};
			T mbidNumber{};
			T trackNumber{};

			for (int i = 0; input[i] != ','; i++) {	// Calculating abid number
				abidNumber = (abidNumber * 10) + (input[i] - 48);
			}

			if (abidNumber == 1) { previousAbid = 1; }	// For first time comparison

			if (previousAbid != abidNumber || queue.isEmpty() /*For storing last AD*/) {
				newAD->abid = previousAbid;
				amdAD->abid = previousAbid;
				insertADInAMD<T, U, V>(newAD, amdAD);	// Developing a two way relationship between AD and AMD
				insertSortedAD<T, U, V>(head, newAD);	// Sorted insertion in AD circular linked list

				if (!queue.isEmpty()) {	// Do not create a new AD if queue becomes empty
					newAD = new AD<T, U, V>();	// Creating a new AD
					amdAD = new AD<T, U, V>();	// Creatinf a new AD for AMD
					infoSaved = false;	// Indicating that information is not saved
				}
			}

			// Saving information from file
			for (int i = 0; input[i] != '\0'; i++) {

				if (input[i] == ',') {
					commaCount = commaCount + 1;

					if (commaCount == 1 && !infoSaved) {	// Tokenizing album name
						string album = "";

						for (int j = i + 1; input[j] != ','; j++) {
							album = album + input[j];
						}

						newAD->albumName = album;	// Setting album name
						amdAD->albumName = album;	// Setting album name for AD of AMD
					}

					else if (commaCount == 2 && !infoSaved) {	// Tokenizing aid number
						string aidNumber = "";

						for (int j = i + 1; input[j] != ','; j++) {
							aidNumber = aidNumber + input[j];
						}

						newAD->aid = stoi(aidNumber);	// Setting aid number
						amdAD->aid = stoi(aidNumber);	// Setting aid number for AD of AMD
					}

					else if (commaCount == 3 && !infoSaved) {	// Tokenizing publisher name
						string publisherName = "";

						for (int j = i + 1; input[j] != ','; j++) {
							publisherName = publisherName + input[j];
						}

						newAD->publisher = publisherName;	// Setting publisher name
						amdAD->publisher = publisherName;	// Setting publisher name for AD of AMD
					}

					else if (commaCount == 4 && !infoSaved) {	// Tokenizing number of tracks
						string noOfTracks = "";

						for (int j = i + 1; input[j] != ','; j++) {
							noOfTracks = noOfTracks + input[j];
						}

						newAD->numberOfTracks = stoi(noOfTracks);	// Setting number of tracks
						amdAD->numberOfTracks = stoi(noOfTracks);	// Setting number of tracks for AD of AMD
					}

					else if (commaCount == 5 && !infoSaved) {	// Tokenizing total duration
						string duration = "";

						for (int j = i + 1; input[j] != ','; j++) {
							duration = duration + input[j];
						}

						newAD->totalDuration = stod(duration);	// Setting total duration
						amdAD->totalDuration = stod(duration);	// Setting total duration for AD of AMD
					}

					else if (commaCount == 6) {	// Tokenizing track number
						string trackNo = "";

						for (int j = i + 1; input[j] != ','; j++) {
							trackNo = trackNo + input[j];
						}

						trackNumber = stoi(trackNo);	// Setting track number
					}

					else if (commaCount == 7) {	// Tokenizing mbid number
						string mbidNo = "";

						for (int j = i + 1; input[j] != '\0'; j++) {
							mbidNo = mbidNo + input[j];
						}

						mbidNumber = stoi(mbidNo);	// Setting mbid number
					}
				}
			}

			infoSaved = true;	// Indicating that information has been saved
			newAD->insertTrack(trackNumber, mbidNumber);	// Inserting track in new AD
			amdAD->insertTrack(trackNumber, mbidNumber);	// Inserting track in new AD of AMD
			previousAbid = abidNumber;	// Updating previous
			insertADInMMD<T, U, V>(newAD, mbidNumber);	// Developing two way relationship between AD and MMD
		}

		ifile.close();	// Closing file

		return head;
	}

	else {	// If file does not opens successfully
		cout << "Error opening file ..." << endl;
		return nullptr;
	}

	// Bad way
	//ifstream ifile;	// Creating file reading object

	//ifile.open(path);	// Opening file

	//if (ifile) {	// If file is opened successfully
	//	string input = "";
	//	Queue<string> queue;
	//	AD<T, U, V>* head = nullptr;	// Creating AD head
	//	T previousAbid{};
	//	bool infoSaved = false;	// To save information other than track just once in AD

	//	getline(ifile, input);	// Skipping first line in file

	//	while (getline(ifile, input)) {	// Reading data from file into the queue
	//		queue.enQueue(input);
	//	}

	//	AD<T, U, V>* newAD = new AD<T, U, V>();	// Creating a new AD
	//	AD<T, U, V>* amdAD = new AD<T, U, V>();	// Creating a new AD to add in AMD

	//	while (!queue.isEmpty()) {
	//		input = queue.getFront()->data; queue.deQueue();	// Getting data from queue (FIFO)
	//		int commaCount = 0;
	//		T abidNumber{};
	//		T mbidNumber{};
	//		T trackNumber{};

	//		for (int i = 0; input[i] != ','; i++) {	// Calculating abid number
	//			abidNumber = (abidNumber * 10) + (input[i] - 48);
	//		}

	//		if (abidNumber == 2 && previousAbid == 1) {
	//			newAD->abid = previousAbid;
	//			amdAD->abid = previousAbid;
	//			insertADInAMD<T, U, V>(newAD, amdAD);	// Developing two way relationship of AD with AMD
	//			insertSortedAD<T, U, V>(head, newAD);	// Sorted insertion in AD circular linked list
	//			newAD = new AD<T, U, V>();	// Creating a new AD
	//			amdAD = new AD<T, U, V>();	// Creatinf a new AD for AMD
	//			infoSaved = false;	// Indicating that information is not saved
	//		}

	//		else if (abidNumber == 3 && previousAbid == 2) {
	//			newAD->abid = previousAbid;
	//			amdAD->abid = previousAbid;
	//			insertADInAMD<T, U, V>(newAD, amdAD);	// Developing two way relationship of AD with AMD
	//			insertSortedAD<T, U, V>(head, newAD);	// Sorted insertion in AD circular linked list
	//			newAD = new AD<T, U, V>();	// Creating a new AD
	//			amdAD = new AD<T, U, V>();	// Creatinf a new AD for AMD
	//			infoSaved = false;	// Indicating that information is not saved
	//		}

	//		else if (abidNumber == 4 && previousAbid == 3) {
	//			newAD->abid = previousAbid;
	//			amdAD->abid = previousAbid;
	//			insertADInAMD<T, U, V>(newAD, amdAD);	// Developing two way relationship of AD with AMD
	//			insertSortedAD<T, U, V>(head, newAD);	// Sorted insertion in AD circular linked list
	//			newAD = new AD<T, U, V>();	// Creating a new AD
	//			amdAD = new AD<T, U, V>();	// Creatinf a new AD for AMD
	//			infoSaved = false;	// Indicating that information is not saved
	//		}

	//		else if (abidNumber == 5 && previousAbid == 4) {
	//			newAD->abid = previousAbid;
	//			amdAD->abid = previousAbid;
	//			insertADInAMD<T, U, V>(newAD, amdAD);	// Developing two way relationship of AD with AMD
	//			insertSortedAD<T, U, V>(head, newAD);	// Sorted insertion in AD circular linked list
	//			newAD = new AD<T, U, V>();	// Creating a new AD
	//			amdAD = new AD<T, U, V>();	// Creatinf a new AD for AMD
	//			infoSaved = false;	// Indicating that information is not saved
	//		}

	//		else if (abidNumber == 6 && previousAbid == 5) {
	//			newAD->abid = previousAbid;
	//			amdAD->abid = previousAbid;
	//			insertADInAMD<T, U, V>(newAD, amdAD);	// Developing two way relationship of AD with AMD
	//			insertSortedAD<T, U, V>(head, newAD);	// Sorted insertion in AD circular linked list
	//			newAD = new AD<T, U, V>();	// Creating a new AD
	//			amdAD = new AD<T, U, V>();	// Creatinf a new AD for AMD
	//			infoSaved = false;	// Indicating that information is not saved
	//		}

	//		else if (abidNumber == 7 && previousAbid == 6) {
	//			newAD->abid = previousAbid;
	//			amdAD->abid = previousAbid;
	//			insertADInAMD<T, U, V>(newAD, amdAD);	// Developing two way relationship of AD with AMD
	//			insertSortedAD<T, U, V>(head, newAD);	// Sorted insertion in AD circular linked list
	//			newAD = new AD<T, U, V>();	// Creating a new AD
	//			amdAD = new AD<T, U, V>();	// Creatinf a new AD for AMD
	//			infoSaved = false;	// Indicating that information is not saved
	//		}

	//		else if (abidNumber == 8 && previousAbid == 7) {
	//			newAD->abid = previousAbid;
	//			amdAD->abid = previousAbid;
	//			insertADInAMD<T, U, V>(newAD, amdAD);	// Developing two way relationship of AD with AMD
	//			insertSortedAD<T, U, V>(head, newAD);	// Sorted insertion in AD circular linked list
	//			newAD = new AD<T, U, V>();	// Creating a new AD
	//			amdAD = new AD<T, U, V>();	// Creatinf a new AD for AMD
	//			infoSaved = false;	// Indicating that information is not saved
	//		}

	//		else if (abidNumber == 9 && previousAbid == 8) {
	//			newAD->abid = previousAbid;
	//			amdAD->abid = previousAbid;
	//			insertADInAMD<T, U, V>(newAD, amdAD);	// Developing two way relationship of AD with AMD
	//			insertSortedAD<T, U, V>(head, newAD);	// Sorted insertion in AD circular linked list
	//			newAD = new AD<T, U, V>();	// Creating a new AD
	//			amdAD = new AD<T, U, V>();	// Creatinf a new AD for AMD
	//			infoSaved = false;	// Indicating that information is not saved
	//		}

	//		else if (abidNumber == 10 && previousAbid == 9) {
	//			newAD->abid = previousAbid;
	//			amdAD->abid = previousAbid;
	//			insertADInAMD<T, U, V>(newAD, amdAD);	// Developing two way relationship of AD with AMD
	//			insertSortedAD<T, U, V>(head, newAD);	// Sorted insertion in AD circular linked list
	//			newAD = new AD<T, U, V>();	// Creating a new AD
	//			amdAD = new AD<T, U, V>();	// Creatinf a new AD for AMD
	//			infoSaved = false;	// Indicating that information is not saved
	//		}

	//		else if (abidNumber == 11 && previousAbid == 10) {
	//			newAD->abid = previousAbid;
	//			amdAD->abid = previousAbid;
	//			insertADInAMD<T, U, V>(newAD, amdAD);	// Developing two way relationship of AD with AMD
	//			insertSortedAD<T, U, V>(head, newAD);	// Sorted insertion in AD circular linked list
	//			newAD = new AD<T, U, V>();	// Creating a new AD
	//			amdAD = new AD<T, U, V>();	// Creatinf a new AD for AMD
	//			infoSaved = false;	// Indicating that information is not saved
	//		}

	//		else if (abidNumber == 12 && previousAbid == 11) {
	//			newAD->abid = previousAbid;
	//			amdAD->abid = previousAbid;
	//			insertADInAMD<T, U, V>(newAD, amdAD);	// Developing two way relationship of AD with AMD
	//			insertSortedAD<T, U, V>(head, newAD);	// Sorted insertion in AD circular linked list
	//			newAD = new AD<T, U, V>();	// Creating a new AD
	//			amdAD = new AD<T, U, V>();	// Creatinf a new AD for AMD
	//			infoSaved = false;	// Indicating that information is not saved
	//		}

	//		else if (abidNumber == 13 && previousAbid == 12) {
	//			newAD->abid = previousAbid;
	//			amdAD->abid = previousAbid;
	//			insertADInAMD<T, U, V>(newAD, amdAD);	// Developing two way relationship of AD with AMD
	//			insertSortedAD<T, U, V>(head, newAD);	// Sorted insertion in AD circular linked list
	//			newAD = new AD<T, U, V>();	// Creating a new AD
	//			amdAD = new AD<T, U, V>();	// Creatinf a new AD for AMD
	//			infoSaved = false;	// Indicating that information is not saved
	//		}

	//		// Saving information from file
	//		for (int i = 0; input[i] != '\0'; i++) {

	//			if (input[i] == ',') {
	//				commaCount = commaCount + 1;

	//				if (commaCount == 1 && !infoSaved) {	// Tokenizing album name
	//					string album = "";

	//					for (int j = i + 1; input[j] != ','; j++) {
	//						album = album + input[j];
	//					}

	//					newAD->albumName = album;	// Setting album name
	//					amdAD->albumName = album;	// Setting album name for AD of AMD
	//				}

	//				else if (commaCount == 2 && !infoSaved) {	// Tokenizing aid number
	//					string aidNumber = "";

	//					for (int j = i + 1; input[j] != ','; j++) {
	//						aidNumber = aidNumber + input[j];
	//					}

	//					newAD->aid = stoi(aidNumber);	// Setting aid number
	//					amdAD->aid = stoi(aidNumber);	// Setting aid number for AD of AMD
	//				}

	//				else if (commaCount == 3 && !infoSaved) {	// Tokenizing publisher name
	//					string publisherName = "";

	//					for (int j = i + 1; input[j] != ','; j++) {
	//						publisherName = publisherName + input[j];
	//					}

	//					newAD->publisher = publisherName;	// Setting publisher name
	//					amdAD->publisher = publisherName;	// Setting publisher name for AD of AMD
	//				}

	//				else if (commaCount == 4 && !infoSaved) {	// Tokenizing number of tracks
	//					string noOfTracks = "";

	//					for (int j = i + 1; input[j] != ','; j++) {
	//						noOfTracks = noOfTracks + input[j];
	//					}

	//					newAD->numberOfTracks = stoi(noOfTracks);	// Setting number of tracks
	//					amdAD->numberOfTracks = stoi(noOfTracks);	// Setting number of tracks for AD of AMD
	//				}

	//				else if (commaCount == 5 && !infoSaved) {	// Tokenizing total duration
	//					string duration = "";

	//					for (int j = i + 1; input[j] != ','; j++) {
	//						duration = duration + input[j];
	//					}

	//					newAD->totalDuration = stod(duration);	// Setting total duration
	//					amdAD->totalDuration = stod(duration);	// Setting total duration for AD of AMD
	//				}

	//				else if (commaCount == 6) {	// Tokenizing track number
	//					string trackNo = "";

	//					for (int j = i + 1; input[j] != ','; j++) {
	//						trackNo = trackNo + input[j];
	//					}

	//					trackNumber = stoi(trackNo);	// Setting track number
	//				}

	//				else if (commaCount == 7) {	// Tokenizing mbid number
	//					string mbidNo = "";

	//					for (int j = i + 1; input[j] != '\0'; j++) {
	//						mbidNo = mbidNo + input[j];
	//					}

	//					mbidNumber = stoi(mbidNo);	// Setting mbid number
	//				}
	//			}
	//		}

	//		infoSaved = true;	// Indicating that information has been saved
	//		newAD->insertTrack(trackNumber, mbidNumber);	// Inserting track in new AD
	//		amdAD->insertTrack(trackNumber, mbidNumber);	// Inserting track in new AD of AMD
	//		previousAbid = abidNumber;	// Updating previous
	//		insertADInMMD<T, U, V>(newAD, mbidNumber);	// Developing two way relationship of AD with MMD
	//	}

	//	newAD->abid = previousAbid;
	//	amdAD->abid = previousAbid;
	//	insertADInAMD<T, U, V>(newAD, amdAD);	// Developing two way relationship of AD with AMD
	//	insertSortedAD<T, U, V>(head, newAD);	// Sorted insertion in AD circular linked list

	//	ifile.close();

	//	return head;
	//}

	//else {	// If file does not opens successfully
	//	cout << "Error opening file ..." << endl;
	//	return nullptr;
	//}
}

template<typename T, typename U = string, typename V = float>
ADP<T>* Create_ADP(string path) //should return head of the ADP linkedlist
{
	// Good way
	ifstream ifile;	// Creating file reading object

	ifile.open(path);	// Opening file

	if (ifile) {	// If file is opened successfully
		string input = "";
		Queue<string> queue;
		ADP<T>* head = nullptr;	// Creating ADP head
		T previousDid{};
		bool infoSaved = false;	// To save information other than track just once in ADP

		getline(ifile, input);	// Skipping first line in file

		while (getline(ifile, input)) {	// Reading data from file into the queue
			queue.enQueue(input);
		}

		ADP<T>* newADP = new ADP<T, U, V>();	// Creating a new ADP
		ADP<T>* amdADP = new ADP<T, U, V>();	// Creating a new ADP to store in AMD

		while (!queue.isEmpty()) {
			input = queue.getFront()->data; queue.deQueue();	// Getting data from queue (FIFO)
			int commaCount = 0;
			T didNumber{};
			T abidNumber{};
			T year{};

			for (int i = 0; input[i] != ','; i++) {	// Calculating did number
				didNumber = (didNumber * 10) + (input[i] - 48);
			}

			if (didNumber == 1) { previousDid = 1; }	// For first time comparison

			if (previousDid != didNumber || queue.isEmpty() /*For storing last ADP*/) {
				newADP->did = previousDid;
				amdADP->did = previousDid;
				insertADPInAMD<T>(newADP, amdADP);	// Developing a two way relationship between ADP and AMD
				insertSortedADP<T>(head, newADP);	// Sorted insertion in ADP circular linked list

				if (!queue.isEmpty()) {	// Do not create a new ADP if queue becomes empty
					newADP = new ADP<T>();	// Creating a new ADP
					amdADP = new ADP<T>();	// Creating a new ADP for storing in AMD
					infoSaved = false;	// Indicating that information is not saved
				}
			}

			// Saving information from file
			for (int i = 0; input[i] != '\0'; i++) {

				if (input[i] == ',') {
					commaCount = commaCount + 1;

					if (commaCount == 1 && !infoSaved) {	// Tokenizing aid number
						string aidNo = "";

						for (int j = i + 1; input[j] != ','; j++) {
							aidNo = aidNo + input[j];
						}

						newADP->aid = stoi(aidNo);	// Setting aid number
						amdADP->aid = stoi(aidNo);	// Setting aid number of ADP for AMD
					}

					else if (commaCount == 2) {	// Tokenizing abid number
						string abidNo = "";

						for (int j = i + 1; input[j] != ','; j++) {
							abidNo = abidNo + input[j];
						}

						abidNumber = stoi(abidNo);	// Setting abid number
					}

					else if (commaCount == 3) {	// Tokenizing year
						string albumYear = "";

						for (int j = i + 1; input[j] != '\0'; j++) {
							albumYear = albumYear + input[j];
						}

						year = stoi(albumYear);	// Setting year
					}
				}
			}

			infoSaved = true;	// Indicating that information has been saved
			newADP->insertAlbum(abidNumber, year);	// Inserting album in new ADP
			amdADP->insertAlbum(abidNumber, year);	// Inserting album in ADP of AMD
			previousDid = didNumber;	// Updating previous
			insertADPInAD<T>(newADP, abidNumber);	// Developing a two way relationship AD to ADP
		}

		ifile.close();	// Closing file

		return head;
	}

	else {	// If file does not opens successfully
		cout << "Error opening file ..." << endl;
		return nullptr;
	}

	// Bad way
	//ifstream ifile;	// Creating file reading object

	//ifile.open(path);	// Opening file

	//if (ifile) {	// If file is opened successfully
	//	string input = "";
	//	Queue<string> queue;
	//	ADP<T>* head = nullptr;	// Creating ADP head
	//	T previousDid{};
	//	bool infoSaved = false;	// To save information other than track just once in ADP

	//	getline(ifile, input);	// Skipping first line in file

	//	while (getline(ifile, input)) {	// Reading data from file into the queue
	//		queue.enQueue(input);
	//	}

	//	ADP<T>* newADP = new ADP<T, U, V>();	// Creating a new ADP
	//	ADP<T>* amdADP = new ADP<T, U, V>();	// Creating a new ADP to store in AMD

	//	while (!queue.isEmpty()) {
	//		input = queue.getFront()->data; queue.deQueue();	// Getting data from queue (FIFO)
	//		int commaCount = 0;
	//		T didNumber{};
	//		T abidNumber{};
	//		T year{};

	//		for (int i = 0; input[i] != ','; i++) {	// Calculating did number
	//			didNumber = (didNumber * 10) + (input[i] - 48);
	//		}

	//		if (didNumber == 2 && previousDid == 1) {
	//			newADP->did = previousDid;
	//			amdADP->did = previousDid;
	//			insertADPInAMD<T>(newADP, amdADP);	// Developing a two way relationship between ADP and AMD
	//			insertSortedADP<T>(head, newADP);	// Sorted insertion in ADP circular linked list
	//			newADP = new ADP<T>();	// Creating a new ADP
	//			amdADP = new ADP<T>();	// Creating a new ADP for storing in AMD
	//			infoSaved = false;	// Indicating that information is not saved
	//		}

	//		else if (didNumber == 3 && previousDid == 2) {
	//			newADP->did = previousDid;
	//			amdADP->did = previousDid;
	//			insertADPInAMD<T>(newADP, amdADP);	// Developing a two way relationship between ADP and AMD
	//			insertSortedADP<T>(head, newADP);	// Sorted insertion in ADP circular linked list
	//			newADP = new ADP<T>();	// Creating a new ADP
	//			amdADP = new ADP<T>();	// Creating a new ADP for storing in AMD
	//			infoSaved = false;	// Indicating that information is not saved
	//		}

	//		else if (didNumber == 4 && previousDid == 3) {
	//			newADP->did = previousDid;
	//			amdADP->did = previousDid;
	//			insertADPInAMD<T>(newADP, amdADP);	// Developing a two way relationship between ADP and AMD
	//			insertSortedADP<T>(head, newADP);	// Sorted insertion in ADP circular linked list
	//			newADP = new ADP<T>();	// Creating a new ADP
	//			amdADP = new ADP<T>();	// Creating a new ADP for storing in AMD
	//			infoSaved = false;	// Indicating that information is not saved
	//		}

	//		else if (didNumber == 5 && previousDid == 4) {
	//			newADP->did = previousDid;
	//			amdADP->did = previousDid;
	//			insertADPInAMD<T>(newADP, amdADP);	// Developing a two way relationship between ADP and AMD
	//			insertSortedADP<T>(head, newADP);	// Sorted insertion in ADP circular linked list
	//			newADP = new ADP<T>();	// Creating a new ADP
	//			amdADP = new ADP<T>();	// Creating a new ADP for storing in AMD
	//			infoSaved = false;	// Indicating that information is not saved
	//		}

	//		// Saving information from file
	//		for (int i = 0; input[i] != '\0'; i++) {

	//			if (input[i] == ',') {
	//				commaCount = commaCount + 1;

	//				if (commaCount == 1 && !infoSaved) {	// Tokenizing aid number
	//					string aidNo = "";

	//					for (int j = i + 1; input[j] != ','; j++) {
	//						aidNo = aidNo + input[j];
	//					}

	//					newADP->aid = stoi(aidNo);	// Setting aid number
	//					amdADP->aid = stoi(aidNo);	// Setting aid number of ADP for AMD
	//				}

	//				else if (commaCount == 2) {	// Tokenizing abid number
	//					string abidNo = "";

	//					for (int j = i + 1; input[j] != ','; j++) {
	//						abidNo = abidNo + input[j];
	//					}

	//					abidNumber = stoi(abidNo);	// Setting abid number
	//				}

	//				else if (commaCount == 3) {	// Tokenizing year
	//					string albumYear = "";

	//					for (int j = i + 1; input[j] != '\0'; j++) {
	//						albumYear = albumYear + input[j];
	//					}

	//					year = stoi(albumYear);	// Setting year
	//				}
	//			}
	//		}

	//		infoSaved = true;	// Indicating that information has been saved
	//		newADP->insertAlbum(abidNumber, year);	// Inserting album in new ADP
	//		amdADP->insertAlbum(abidNumber, year);	// Inserting album in ADP of AMD
	//		previousDid = didNumber;	// Updating previous
	//		insertADPInAD<T>(newADP, abidNumber);	// Developing a two way relationship AD to ADP
	//	}

	//	newADP->did = previousDid;
	//	amdADP->did = previousDid;
	//	insertADPInAMD<T>(newADP, amdADP);	// Developing a two way relationship between ADP and AMD
	//	insertSortedADP<T>(head, newADP);	// Sorted insertion in ADP circular linked list

	//	ifile.close();	// Closing file

	//	return head;
	//}

	//else {	// If file does not opens successfully
	//	cout << "Error opening file ..." << endl;
	//	return nullptr;
	//}
}

template<typename T, typename U, typename V>
MMD<T, U, V>* Search_Music(int MBID) //should return pointer to track having mbid = MBID
{
	if (mmd == nullptr) { return nullptr; }	// If MMD is empty
	MMD<T, U, V>* targetMMD = mmd;

	while (targetMMD != nullptr && targetMMD->mbid != MBID) {
		targetMMD = targetMMD->next;
	}

	return targetMMD;
}

template<typename T, typename U, typename V = float>
AMD<T, U>* Search_Author(int AID) //should return pointer to author having aid = AID
{
	if (amd == nullptr) { return nullptr; }	// If AMD is empty
	AMD<T, U>* targetAMD = amd;

	while (targetAMD->next != amd) {
		if (targetAMD->aid == AID) { return targetAMD; }
		targetAMD = targetAMD->next;
	}

	if (targetAMD->aid == AID) { return targetAMD; }	// Checking last AMD
	return nullptr;
}

template<typename T, typename U, typename V>
AD<T, U, V>* Search_Album(int ABID) //should return pointer to album having abid = ABID
{
	if (ad == nullptr) { return nullptr; }	// If AD is empty
	AD<T, U, V>* targetAD = ad;

	while (targetAD->next != ad) {
		if (targetAD->abid == ABID) { return targetAD; }
		targetAD = targetAD->next;
	}

	if (targetAD->abid == ABID) { return targetAD; }	// Checking last AD
	return nullptr;
}

template<typename T, typename U = string, typename V = float>
ADP<T>* Search_Discography(int DID) //should return pointer to discography having did = DID
{
	if (adp == nullptr) { return nullptr; }	// If ADP is empty
	ADP<T>* targetADP = adp;

	while (targetADP->next != adp) {
		if (targetADP->did == DID) { return targetADP; }
		targetADP = targetADP->next;
	}

	if (targetADP->did == DID) { return targetADP; }	// Checking last ADP
	return nullptr;
}

template<typename T, typename U = string, typename V = float>
Tracks<T>* Search_Music_By_Album(int ABID) //should return singly linklist of "Tracks" in given album
{
	if (ad == nullptr) { return nullptr; }	// If AD is empty
	AD<T, U, V>* targetAD = ad;

	while (targetAD->next != ad) {
		if (targetAD->abid == ABID) { return targetAD->tracks; }
		targetAD = targetAD->next;
	}

	if (targetAD->abid == ABID) { return targetAD->tracks; }	// Checking last AD
	return nullptr;
}

template<typename T, typename U = string, typename V = float>
Albums<T, U, V>* Search_Music_By_Author(int DID) //should return singly linklist of "Albums" in given discography
{
	if (adp == nullptr) { return nullptr; }	// If ADP is empty
	ADP<T>* targetADP = adp;

	while (targetADP->next != adp) {
		if (targetADP->did == DID) { return targetADP->albums; }
		targetADP = targetADP->next;
	}

	if (targetADP->did == DID) { return targetADP->albums; }	// Checking last ADP
	return nullptr;
}