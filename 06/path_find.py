#!/usr/bin/env python3

turn_right = {
    (0, 1) : (1, 0),
    (1, 0) : (0, -1),
    (0, -1) : (-1, 0),
    (-1, 0) : (0, 1)
}


def clear_moves():
    global moves
    moves = [[0 for _ in range(130)] for _ in range(130)]



def get_input():
    text = []
    with open("map.in", "r") as fileP:
        while (line := fileP.readline()):
            text.append(line[:-1])
    return text


def get_start():
    for i in range(130):
        if '^' in text[i]:
            for j in range(130):
                if text[i][j] == '^':
                    return [i, j]



text = get_input()
pos = get_start()
direction = (0, -1)
clear_moves()


def move():
    global pos
    global direction
    global moves
    if 0 <= pos[0] + direction[0] <= 129 and 0 <= pos[1] + direction[1] <= 129:
        for i in range(4):
            if text[pos[0] + direction[0]][pos[1] + direction[1]] == '#':
                direction = turn_right[direction]
                if 0 <= pos[0] + direction[0] <= 129 and 0 <= pos[1] + direction[1] <= 129:
                    continue
                else:
                    return False
            moves[pos[0]][pos[1]] += 1
            pos[0] = pos[0] + direction[0]
            pos[1] = pos[1] + direction[1]
            return True
    else:
        return False


def do_moves():
    while(move()):
        if moves[pos[0]][pos[1]] > 5:
            return 1
    return 0


count = 0
for i in range(130):
    for j in range(130):
        if text[i][j] in "^#":
            continue
        text[i] = text[i][:j] + '#' + text[i][j + 1:]
        count += do_moves()
        text[i] = text[i][:j] + '.' + text[i][j + 1:]
        clear_moves()
        pos = get_start()
        direction = (0, -1)




print(count)
