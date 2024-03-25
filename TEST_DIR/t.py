# Открываем файл для чтения
with open('test_9_ans_113_241.txt', 'r') as file:
    # Инициализируем счетчики для отрицательных и положительных чисел
    negative_count = 0
    positive_count = 0

    # Проходим по строкам файла
    for line in file:
        # Разбиваем строку на слова
        words = line.split()

        # Проходим по словам и пытаемся преобразовать их в целые числа
        for word in words:
            try:
                number = int(word)
                if number < 0:
                    negative_count += 1
                elif number > 0:
                    positive_count += 1
            except ValueError:
                # Если не удается преобразовать в число, игнорируем
                pass

# Выводим результаты
print("Количество положительных чисел:", positive_count)
print("Количество отрицательных чисел:", negative_count)

