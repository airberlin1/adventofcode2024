#!/usr/bin/env python3


# this works and gets an answer in a bout 20min
#
# after checking the subreddit I realize that actually doing what I did here manually with saving once is fairly trivially extended to memorizing everything, I just didn't figure it out on my own
# eventually, the haskell program should make use of a similar, but different approach that runs faster

found_stones = [0 for _ in range(1000)]

def blink(stones):
    new_stones = []
    for stone in stones:
        if stone == 0:
            new_stones.append(1)
        elif (l:=len(str(stone))) % 2 == 0:
            new_stones.append(int(stone % (10 ** (l/2))))
            new_stones.append(int(stone / (10 ** (l/2))))
        else:
            new_stones.append(stone * 2024)

    return new_stones


def blinkOften(stones, amount):
    for i in range(amount):
        stones = blink(stones)
    for stone in stones:
        if stone < 1000:
            found_stones[stone] += 1
    if amount == 35:
        return len(stones)
    return stones


mem = [blinkOften([i], 35) for i in range(50)]

with open("stones.in", "r") as fp:
    text = fp.read()
    ints = [int(s) for s in text.split(" ")]


blobs = blinkOften(ints, 40)

new_blobs = []

thirty_five_dic = {
    0 : mem[0]
}
count = 0
for blob in blobs:
    if blob < 50:
        count += mem[blob]
    elif blob in thirty_five_dic:
        count += thirty_five_dic[blob]
    else:
        thirty_five_dic[blob] = blinkOften([blob], 35)
        count += thirty_five_dic[blob]

print(count)
