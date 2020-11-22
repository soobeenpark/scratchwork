#ifndef GNOMESORT_CPP
#define GNOMESORT_CPP

#include <algorithm>

/* @brief Gnome Sort algorithm */
void gnomeSort(int arr[], long len) {
    int pos = 0;

    while (pos < len) {
        if (pos == 0) {
            pos++;
        }

        if (pos < len && arr[pos - 1] > arr[pos]) {
            std::swap(arr[pos - 1], arr[pos]);
            pos--;
        } else {
            pos++;
        }
    }
}

#endif // GNOMESORT_CPP
