// This is a program that asks the user for two matrices up to size of 10*10
// Then can do a limited number of operations on them
// A+B, A-B, B-A, A*B, B*A, A*inv(B), B*inv(A), |A|, |B|
#include <iostream>
#include <cmath>
#include "operations.h"
using namespace std;
// main function
int main()
{
    int ar, ac, br, bc;

    cout << "Please enter dimensions of Matrix A:" << endl;
    cin >> ar >> ac;

    cout << "Please enter dimensions of Matrix B:" << endl;
    cin >> br >> bc;

    int a[10][10], b[10][10];

    cout << "Please enter values of Matrix A:" << endl;
    for (int i = 0; i < ar; i++)
    {
        for (int j = 0; j < ac; j++)
        {
            cin >> a[i][j];
        }
    }

    cout << "Please enter values of Matrix B:" << endl;
    for (int i = 0; i < br; i++)
    {
        for (int j = 0; j < bc; j++)
        {
            cin >> b[i][j];
        }
    }

    int operation;
    do
    {
        cout << "Please choose operation type\n(1: A+B, 2: A-B, 3: B-A, 4: A×B, 5: B×A, 6: A×inverse(B), 7: B×inverse(A), 8: |A|, 9: |B|, 10: quit):" << endl;
        cin >> operation;

        switch (operation)
        {
        // A+B
        case 1:
            if (ar == br && ac == bc)
            {
                for (int i = 0; i < ar; i++)
                {
                    for (int j = 0; j < ac; j++)
                    {
                        cout << round(a[i][j] + b[i][j]) << " ";
                    }
                    cout << endl;
                }
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices." << endl;
            }
            break;
        // A-B
        case 2:
            if (ar == br && ac == bc)
            {
                for (int i = 0; i < ar; i++)
                {
                    for (int j = 0; j < ac; j++)
                    {
                        cout << round(a[i][j] - b[i][j]) << " ";
                    }
                    cout << endl;
                }
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices." << endl;
            }
            break;
        // B-A
        case 3:
            if (br == ar && bc == ac)
            {
                for (int i = 0; i < br; i++)
                {
                    for (int j = 0; j < bc; j++)
                    {
                        cout << round(b[i][j] - a[i][j]) << " ";
                    }
                    cout << endl;
                }
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices." << endl;
            }
            break;
        // A*B
        case 4:
            if (ac == br)
            {
                multiply(a, b, ar, ac, bc);
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices." << endl;
            }
            break;
        // B*A
        case 5:
            if (bc == ar)
            {
                multiply(b, a, br, bc, ac);
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices." << endl;
            }
            break;
        // A/B
        case 6:
            if (br == bc && ac == br && det(b, br) != 0)
            {
                divide(a, b, ar, ac);
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices." << endl;
            }
            break;
        // B/A
        case 7:
            if (ar == ac && bc == ar && det(a, ar) != 0)
            {
                divide(b, a, br, bc);
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices." << endl;
            }
            break;
        // |A|
        case 8:
            if (ar == ac)
            {
                cout << det(a, ar) << endl;
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices." << endl;
            }
            break;
        // |B|
        case 9:
            if (br == bc)
            {
                cout << det(b, br) << endl;
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices." << endl;
            }
            break;
        }
    } while (operation != 10);

    cout << "Thank you!" << endl;
    return 0;
}