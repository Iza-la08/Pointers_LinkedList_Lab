#include "Inventory.h"
#include <iostream>
#include <algorithm>

// Constructor
Inventory::Inventory() {
    // Vector is automatically initialized as empty
	head = nullptr;
}

// Destructor - Important! Clean up dynamically allocated memory
Inventory::~Inventory() {
    // Delete all Book objects to prevent memory leaks
	Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp->data; // Free the Book memory
        delete temp;       // Free the Node memory
    }
}

// Add a book to the inventory (sorted by title alphabetically)//
void Inventory::addBook(Book* bookPtr) {
    if (!bookPtr) return;

    Node* newNode = new Node(bookPtr);

    if (!head || bookPtr->getTitle() < head->data->getTitle()) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next && current->next->data->getTitle() < bookPtr->getTitle()) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// Display all books in the inventory
    void Inventory::displayAll() const {
        if (!head) {
            std::cout << "No books in inventory.\n";
            return;
        }

        Node* current = head;
        int count = 1;
        while (current) {
            std::cout << "Book #" << count++ << ":\n";
            current->data->displayInfo();
            current = current->next;
        }
    }

// Remove a book by title
void Inventory::removeBook(const std::string& title) {
	if (!head) return;

    if (head->data->getTitle() == title) {
        Node* temp = head;
        head = head->next;
        delete temp->data; // Free the Book memory
        delete temp;       // Free the Node memory
		std::cout << "Removed book: " << title << "\n";
        return;
	}

    Node* current = head;
    while (current->next && current->next->data->getTitle() != title) {
        current = current->next;
    }

    if (current->next) {
        Node* temp = current->next;
        current->next = temp->next;
        delete temp->data;
        delete temp;
        std::cout << "Removed book: " << title << "\n";
    }
    else {
        std::cout << "Book '" << title << "' not found.\n";
    }

}

// Get the number of books//
size_t Inventory::getBookCount() const {
	size_t count = 0;
	Node* current = head;
    while (current) {
        count++;
        current = current->next;
    }
	return count;
}

// Search for a book by title //
Book* Inventory::findBook(const std::string& title) const {
	Node* current = head;
    while (current) {
        if (current->data->getTitle() == title)
            return current->data;
        current = current->next;
    }
	return nullptr;
}

// Check if inventory is empty //
bool Inventory::isEmpty() const {
    return head == nullptr;
}