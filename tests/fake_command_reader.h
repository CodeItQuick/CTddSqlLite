//
// Created by Owner on 5/11/2024.
//

#pragma once

struct commands {
    char commandList[3][40];
};

char* commands_reader(struct commands commands, int len);
