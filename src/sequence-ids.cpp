#include <vector>
#include <stdio.h>

int main(int argv, char** args) {
    fprintf(stdout, "Sequence ids example!\n");

    // This vector contains an entry for each token and specifies the  number
    // of sequences that a token belongs to.
    // that this token belongs to.
    std::vector<int32_t> n_seq_id;
    n_seq_id.resize(3);
    n_seq_id[0] = 1; // only has one sequence id.
    n_seq_id[1] = 2; // has two sequence ids. So the seq_id for this index will have two entries.
    n_seq_id[2] = 3; // has three sequence ids.

    // This the outer vector which contains vectors.
    // seq_id: [ vector1, vector2, vector3 ... ]
    std::vector<std::vector<int>> seq_id;
    fprintf(stdout, "seq_id len: %d\n", seq_id.size());

    // This is the inner vector of seq_id.
    // seq_id_arr: [ int*, int*, int* ... ]
    std::vector<int*> seq_id_arr;
    fprintf(stdout, "seq_id_arr len: %d\n", seq_id_arr.size());

    seq_id_arr.resize(3);
    fprintf(stdout, "seq_id_arr len: %d\n", seq_id_arr.size());

    seq_id.resize(3);
    fprintf(stdout, "seq_id len: %d\n", seq_id.size());

    // seq_id_arr is an array of pointers, which are initialized to nullptr
    fprintf(stdout, "seq_id_arr:\n");
    for (int i = 0; i < seq_id_arr.size(); i++) {
        fprintf(stdout, "seq_id_arr[%d]: %p\n", i, seq_id_arr[i]);
    }

    fprintf(stdout, "seq_id:\n");
    for (int i = 0; i < seq_id.size(); i++) {
        fprintf(stdout, "seq_id[%d]: %p\n", i, &seq_id[i]);
    }

    // So we first create the inner vector which will only contain one element:
    seq_id[0].resize(1);
    // Now we can set this newly created elements value:
    seq_id[0][0] = 0;
    // Next we want to add a new element to the outer vector:
    seq_id_arr[0] = seq_id[0].data();

    seq_id[1].resize(2);
    seq_id[1][0] = 1;
    seq_id[1][1] = 2;
    seq_id_arr[1] = seq_id[1].data();

    fprintf(stdout, "seq_id_arr:\n");
    for (int i = 0; i < seq_id_arr.size(); i++) {
        if (seq_id_arr[i] != nullptr) {
            for (int j = 0; j < seq_id[i].size(); j++) {
                fprintf(stdout, "seq_id_arr[%d][%d]: %d\n", i, j, seq_id_arr[i][j]);
            }
        } else {
            fprintf(stdout, "seq_id_arr[%d]: nullptr\n", i);
        }
    }


}
