#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef struct Node* Nodeptr;

struct Node
{
    string name;
    string role;
    Nodeptr next;
};

class PriorityQueue
{
private:
    Nodeptr head;

    int getPriority(string role)
    {
        if (role == "Parent") return 3;
        else if (role == "Teacher") return 2;
        else if (role == "Student") return 1;
        return 0;
    }

public:
    PriorityQueue() : head(NULL) {}

    void insert(string name, string role)
    {
        int priority = getPriority(role);
        Nodeptr newNode = new Node{ name, role, NULL };

        if (!head || priority > getPriority(head->role))
        {
            newNode->next = head;
            head = newNode;
        }
        else
        {
            Nodeptr current = head;

            while (current->next)
            {
                if (priority > getPriority(current->next->role))
                {
                    break;
                }
                current = current->next;
            }

            newNode->next = current->next;
            current->next = newNode;
        }
    }

    void display()
    {
        Nodeptr temp = head;
        while (temp)
        {
            cout << temp->name << " - " << temp->role << "\n";
            temp = temp->next;
        }
    }

    ~PriorityQueue()
    {
        while (head)
        {
            Nodeptr temp = head;
            head = head->next;
            delete temp;
        }
    }
};

void readAndPopulate(PriorityQueue& pq, const string& filename)
{
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "Error: Could not open the file.\n";
        return;
    }

    string name, role;
    while (infile >> name >> role)
    {
        pq.insert(name, role);
    }
    infile.close();
}

int main()
{
    PriorityQueue pq;
    string filename = "Text.txt";
    readAndPopulate(pq, filename);

    cout << "Priority Queue (Parent > Teacher > Student):\n";
    pq.display();

    return 0;
}
