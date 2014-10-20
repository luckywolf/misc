 int atoi(const char *str) {
        int res = 0;
        if (!str) {
            return res;
        }
        while (*str == ' ') {
            str++;
        }
        bool positive = true;
        if (*str == '+') {
            str++;
        } else if (*str == '-') {
            str++;
            positive = false;
        }
        while (isdigit(*str)) {
            if (INT_MAX / 10 < res || 
                INT_MAX / 10 == res && INT_MAX % 10 < *str - '0') { // Be cautious, possible bugs
                return positive ? INT_MAX : INT_MIN;  
            }
            res = res * 10 + *str - '0';
            str++; // Be cautious, possible bugs
        }
        return positive ? res : -res; 

    }