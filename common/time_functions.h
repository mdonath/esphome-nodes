struct TimeDiffDays {
    uint16_t days;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
};


time_t parse_datestring(std::string &datestring) {
    struct tm timeinfo = {0};
    strptime(datestring.c_str(), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return mktime(&timeinfo);
}

void calculate_diff(TimeDiffDays *tdd, time_t target, time_t now) {
    time_t n = abs(difftime(target, now));
    
    tdd->days = n / (24 * 3600);

    n = n % (24 * 3600);
    tdd->hours = n / 3600;

    n %= 3600;
    tdd->minutes = n / 60;

    n %= 60;
    tdd->seconds = n;
}
