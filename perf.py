def calculate_perfect_cache_hits(buffer_size, input_size, input_buffer)->int:
    if len(input_buffer) != input_size:
        return -1
    hits = 0
    cache = []

    for i in range(len(input_buffer)):
        if input_buffer[i] in [j[0] for j in cache]:
            hits += 1
        else:
            cache.append([input_buffer[i], 0])
        for j in range(len(cache)):
            if cache[j][0] not in input_buffer[i+1::]:
                cache[j][1] = len(input_buffer[i+1::])
            else:
                cache[j][1] = input_buffer[i+1::].index(cache[j][0])
        cache = sorted(cache,key = lambda x: x[1])

        if len(cache) > buffer_size:
            cache.pop()

    return hits
def main():
    # Принимаем ввод данных
    data = list(map(int, input().split()))

    # Разбиваем на переменные
    cache_capacity = data[0]
    input_size = data[1]
    elements = data[2:]

    # Вызываем функцию calculate_perfect_cache_hits и выводим результат
    hit_count = calculate_perfect_cache_hits(cache_capacity, input_size, elements)
    print(f"Hits count: {hit_count}")

if __name__ == "__main__":
    main()

