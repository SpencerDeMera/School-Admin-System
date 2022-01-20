#ifndef AL_DICT_H
#define AL_DICT_H

#include "Dictionary.hpp"
#include "ArrayList.hpp"
#include <iomanip>

template <typename Key, typename Val>
class ALDict : public Dictionary<Key, Val> {
    private:
        // an element in a dictionary, contains a key and a value
        struct Record {
            Key k;
            Val v;

            Record() {
                k = Key{};
                v = Val{};
            }

            Record(Key x, Val y) {
                k = x;
                v = y;
            }

			// T(n) = O(1)
            bool operator<(const Record& rightObj) const {
                return this->k < rightObj.k;
            }

			// T(n) = O(1)
            bool operator<=(const Record& rightObj) const {
                return this->k <= rightObj.k;
            }

			// T(n) = O(1)
            bool operator>(const Record& rightObj) const {
                return this->k > rightObj.k;
            }

			// T(n) = O(1)
            bool operator>=(const Record& rightObj) const {
                return this->k >= rightObj.k;
            }

			// T(n) = O(1)
            bool operator==(const Record& rightObj) const {
                return this->k == rightObj.k;
            }

			// T(n) = O(1)
            bool operator!=(const Record& rightObj) const {
                return this->k != rightObj.k;
            }

            friend
            ostream& operator<<(ostream& outStream, const Record& myObj) {
                outStream << "(" << myObj.k << ", " << myObj.v << ")\n";
                return outStream;
            }
        };

        // the underlying array-based list
        ArrayList<Record>* list;

    public:
        // default constructor
        ALDict(int = 100);

        // destructor
        virtual ~ALDict();

        // remove all records in the dictionary
        virtual void clear() override;

        // retrieve the record that matches the argument key
        // if multiple records match, return an arbitrary one
        virtual Val find(const Key&) const override;

		virtual Val getPerf(int position) const override;

        // add the record as a key-value pair to the dictionary
        virtual void insert(const Key&, const Val&) override;

        // print the records in the dictionary
        virtual void print() const override;

        // remove the record that matches the argument key from the dictionary
        // if multiple records match, remove an arbitrary one
        virtual void remove(const Key&) override;

        // return the number of records in the dictionary
        virtual int size() const override;

        // sort the records in the dictionary using the algorithm (argument 1)
        //      1 --> bubble sort
        //      2 --> selection sort
        //      3 --> insertion sort
        //      4 --> merge sort
        //      5 --> quicksort
        virtual void sort(int) override;
};

// T(n) = O(1)
template <typename Key, typename Val>
ALDict<Key, Val>::ALDict(int i) {
    list = new ArrayList<Record>(i);
}

// T(n) = O(1)
template <typename Key, typename Val>
ALDict<Key, Val>::~ALDict() {
    delete list;
}

// T(n) = O(1)
template <typename Key, typename Val>
void ALDict<Key, Val>::clear() {
    list->clear();
}

// T(n) = O(n)
template <typename Key, typename Val>
Val ALDict<Key, Val>::find(const Key& target) const {
    Record r;

    for (int i = 0; i < list->getLength(); i++) {
        r = list->getElement(i);
        if (r.k == target) {
            return r.v;
        } // if
    } // for loop

    cout << "ERROR: unable to find record\n";
    throw -1;
}

// T(n) = O(n)
template <typename Key, typename Val>
Val ALDict<Key, Val>::getPerf(int position) const {
    Record r;
	if (position >= 0 && position < list->getLength()) {
		r = list->getElement(position);
    	return r.v;
	} // if
	else {
		cout << "ERROR: unable to find record\n";
    	throw -1;
	} // else
}

// T(n) = O(n)
template <typename Key, typename Val>
void ALDict<Key, Val>::insert(const Key& k, const Val& v) {
    list->append(Record(k, v));
}

// T(n) = O(n)
template <typename Key, typename Val>
void ALDict<Key, Val>::print() const {
    const char FILL = '-';
    const int WIDTH = 80;
    const int SLOT_WIDTH = 4;
    const int KEY_WIDTH = 25;
    Record r;

    if (size() == 0) {
        cout << "Dictionary is empty!\n";
        return;
    } // if

    cout << setfill(FILL) << setw(WIDTH) << "" << endl << setfill(' ');

    for (int i = 0; i < list->getLength(); i++) {
        r = list->getElement(i);
        cout << right << setw(SLOT_WIDTH) << i << " | "
             << left << setw(KEY_WIDTH)
             << r.k << " | " << r.v << endl;
    } // for loop

    cout << setfill(FILL) << setw(WIDTH) << "" << endl;
}

// T(n) = O(n)
template <typename Key, typename Val>
void ALDict<Key, Val>::remove(const Key& k) {
    bool flag = false;

    for (int i = 0; i < list->getLength(); i++) {
        if (list->getElement(i).k == k) {
            list->remove(i);
            flag = true;
            break;
        } // if
    } // for loop

    if (!flag) {
        cout << "Unable to find record with matching key to remove\n";
    } // if
}

// T(n) = O(1)
template <typename Key, typename Val>
int ALDict<Key, Val>::size() const {
    return list->getLength();
}

// T(n) = O(1)
template <typename Key, typename Val>
void ALDict<Key, Val>::sort(int algo) {
    list->sort(algo);
}

#endif
