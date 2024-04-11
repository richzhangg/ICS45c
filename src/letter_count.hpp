int char_to_index(char ch)
{
	if (ch >= 'A' && ch <= 'Z'){
	return ch - 'A';
	} else if (ch >= 'a' && ch <= 'z') {
	return ch - 'a';
	}
}
char index_to_char(int i)
{
	if (i == 0) {
        return 'A';
    } else if (i == 1) {
        return 'B';
    } else if (i == 2) {
        return 'C';
    } else if (i == 3) {
        return 'D';
    } else if (i == 4) {
        return 'E';
    } else if (i == 5) {
        return 'F';
    } else if (i == 6) {
        return 'G';
    } else if (i == 7) {
        return 'H';
    } else if (i == 8) {
        return 'I';
    } else if (i == 9) {
        return 'J';
    } else if (i == 10) {
        return 'K';
    } else if (i == 11) {
        return 'L';
    } else if (i == 12) {
        return 'M';
    } else if (i == 13) {
        return 'N';
    } else if (i == 14) {
        return 'O';
    } else if (i == 15) {
        return 'P';
    } else if (i == 16) {
        return 'Q';
    } else if (i == 17) {
        return 'R';
    } else if (i == 18) {
        return 'S';
    } else if (i == 19) {
        return 'T';
    } else if (i == 20) {
        return 'U';
    } else if (i == 21) {
        return 'V';
    } else if (i == 22) {
        return 'W';
    } else if (i == 23) {
        return 'X';
    } else if (i == 24) {
        return 'Y';
    } else if (i == 25) {
        return 'Z';
    }
}
void count(string s, int counts[]) {
    for (char ch : s) {
        if (isalpha(ch)) {
            int index = char_to_index(ch);
			if (index != -1) {
                ++counts[index];
            }
        }
    }
}
void print_counts(int counts[], int len) {
	for (int i = 0; i < len; ++i) {
		char index_char = index_to_char(i);
		std::cout << index_char << ' ' << counts[i] << endl;
	}
}
