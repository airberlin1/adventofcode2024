#!/usr/bin/env python3


def test_printer_update(update, rules):
    for i, page in enumerate(update):
        for rule in rules:
            # Widerspruch finden?
            if page == rule[1]:
                if rule[0] in update[i:]:
                    return 0
    return update[int(len(update) / 2)]


def first_star():
    rules = []
    updates = []
    with open("printer_rules.in", "r") as read_file:
        while (line := read_file.readline()) != "\n":
            split_line = line.split("|")
            new_rule = [int(split_line[i]) for i in range(2)]
            rules.append(new_rule)

        while(line := read_file.readline()):
            split_line = line.split(",")
            new_update = [int(num) for num in split_line]
            updates.append(new_update)

    result = 0
    for update in updates:
        result += test_printer_update(update, rules)
    print(result)
    snd_result = 0
    inc_updates = [update for update in updates if test_printer_update(update, rules) == 0]
    for update in inc_updates:
        snd_result += sort_upt(update, rules)
    print(snd_result)


def assemble_incorrect_updates(updates,rules):
    def get_inc_update(update_i):
        for i, page in enumerate(update_i):
            for rule in rules:
            # Widerspruch finden?
                if page == rule[1]:
                    if rule[0] in update_i[i:]:
                        return update_i
        return False

    incorrectupdates = []
    for update in updates:
        if new_inc := get_inc_update(update):
            incorrectupdates.append(new_inc)
    return incorrectupdates



def swap_update_items(i,j, update):
    zwischenspeicher = update[i]
    update[i] = update[j]
    update[j] = zwischenspeicher


def sort_update(update, rules):
    for i, page in enumerate(update):
        for rule in rules:
            # Widerspruch finden?
            if page == rule[1]:
                if rule[0] in update[i:]:
                    swap_update_items(i,update.index(rule[0]))


def page_wrong():
    pass


def swap(i, j):
    return j, i


def sort_upt(update, rules):
    swapped = True
    while(swapped):
        swapped = False
        for i, page in enumerate(update):
            for rule in rules:
                if page == rule[0]:
                    for j in range(i):
                        if rule[1] == update[j]:
                            update[j], update[i] = swap(update[j], update[i])
                            swapped = True
                            break
    return update[int(len(update) / 2)]


if __name__ == '__main__':
    first_star()
