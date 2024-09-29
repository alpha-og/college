def lengthOfLongestSubstring(s: str) -> int:
    max = 0
    i = 0
    j = 0
    while i < len(s) and j < len(s):
        substring = s[i : j + 1]
        if len(substring) != len(set(substring)):
            i += 1
        else:
            if max < len(substring):
                max = len(substring)
            j += 1

    return max


print(lengthOfLongestSubstring(" "))
