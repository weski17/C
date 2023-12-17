#ifndef EXAMPLE_H
#define EXAMPLE_H

class Example {
private:
    int privateData;

public:
    Example() = default;  // Default constructor declaration
    Example(int data);     // Constructor declaration
    void displayPrivateData(); // Member function declaration
    friend void funktion(Example& ex); // Friend function declaration
};

#endif
