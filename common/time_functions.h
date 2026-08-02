struct TimeDiffDays {
    uint16_t days;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
};

void calculate_diff(TimeDiffDays *tdd, ESPTime target, ESPTime now) {
    time_t n = abs(difftime(target.timestamp, now.timestamp));
    
    tdd->days = n / (24 * 3600);

    n = n % (24 * 3600);
    tdd->hours = n / 3600;

    n %= 3600;
    tdd->minutes = n / 60;

    n %= 60;
    tdd->seconds = n;
}
