#ifndef CONFIG_H
#define CONFIG_H

// String used to delimit block outputs in the status.
#define DELIMITER " | "

// Maximum number of Unicode characters that a block can output.
#define MAX_BLOCK_OUTPUT_LENGTH 45

// Control whether blocks are clickable.
#define CLICKABLE_BLOCKS 0

// Control whether a leading delimiter should be prepended to the status.
#define LEADING_DELIMITER 0

// Control whether a trailing delimiter should be appended to the status.
#define TRAILING_DELIMITER 0

// Define blocks for the status feed as X(icon, cmd, interval, signal).
#define BLOCKS(X)             \
    X("", "blocks-musicplaying", 1, 0) \
    X("", "blocks-volume", 10, 12) \
    X("", "blocks-systemstats", 30, 0) \
    X("", "blocks-disks", 600, 0) \
    X("", "~/Dev/dwl/someblocks/scripts/weather", 300, 0) \
    X("", "blocks-timedate", 1, 10)

#endif  // CONFIG_H
