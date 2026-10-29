#ifndef LAB07_PART_B_DOUBLY_LIST_H
#define LAB07_PART_B_DOUBLY_LIST_H

/* Name: M.Haroon-Ur-Rasheed Khan | Reg. No: Ai-9 | Subject: DSA | Sec: A */
// Lab 07 Part B: Individual library borrowing session

#include <iostream>
#include <string>

using namespace std;

struct BookNode
{
    int id;
    string title;
    BookNode* left;
    BookNode* right;

    BookNode(int bookID, const string& bookTitle)
        : id(bookID), title(bookTitle), left(nullptr), right(nullptr) {}
};

class BorrowingSession
{
private:
    BookNode* head;
    BookNode* tail;
    BookNode* current;

    void clear()
    {
        while (head != nullptr)
            delete RemoveCurrent();
    }

public:
    BorrowingSession()
        : head(nullptr), tail(nullptr), current(nullptr) {}

    ~BorrowingSession() { clear(); }

    bool IsEmpty() const { return head == nullptr; }
    bool IsNotEmpty() const { return head != nullptr; }

    void InsertRight(BookNode* book)
    {
        if (book == nullptr)
            return;

        book->left = tail;
        book->right = nullptr;

        if (tail != nullptr)
            tail->right = book;
        else
            head = book;

        tail = book;
        if (current == nullptr)
            current = book;
    }

    void Next()
    {
        if (current != nullptr && current->right != nullptr)
            current = current->right;
    }

    void Previous()
    {
        if (current != nullptr && current->left != nullptr)
            current = current->left;
    }

    void InsertAfterCurrent(BookNode* book)
    {
        if (book == nullptr)
            return;

        if (current == nullptr)
        {
            InsertRight(book);
            return;
        }

        book->left = current;
        book->right = current->right;

        if (current->right != nullptr)
            current->right->left = book;
        else
            tail = book;

        current->right = book;
    }

    BookNode* RemoveCurrent()
    {
        if (current == nullptr)
            return nullptr;

        BookNode* removed = current;
        BookNode* previous = removed->left;
        BookNode* next = removed->right;

        if (previous != nullptr)
            previous->right = next;
        else
            head = next;

        if (next != nullptr)
            next->left = previous;
        else
            tail = previous;

        current = (next != nullptr) ? next : previous;
        removed->left = nullptr;
        removed->right = nullptr;
        return removed;
    }

    void PrintForward() const
    {
        cout << "\nForward session:\n";
        for (BookNode* node = head; node != nullptr; node = node->right)
        {
            cout << node->id << " - " << node->title;
            if (node == current)
                cout << " [CURRENT]";
            cout << '\n';
        }
    }

    void PrintBackward() const
    {
        cout << "\nBackward session:\n";
        for (BookNode* node = tail; node != nullptr; node = node->left)
        {
            cout << node->id << " - " << node->title;
            if (node == current)
                cout << " [CURRENT]";
            cout << '\n';
        }
    }
};

#endif
