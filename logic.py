import os.path
from tkinter import filedialog

import errors
import info_messages
import interface
from getters import get_and_print_metrics, get_region_and_column, get_viable_int_number

ACCEPTABLE_FILE_SIZE_MB = 1


def initialize():
    program_phase = 0  # Первая стадия программы, файл не был выбран, почти ничего нельзя делать
    while True:
        interface.print_interface()

        choice = get_viable_int_number(5, info_messages.InfoMessages.interface_input_info)

        if choice == 1:  # Выбираем файл
            selected_file = select_csv_file()
            if selected_file:
                print(f"{info_messages.InfoMessages.file_select_success}{selected_file}")
                program_phase = 1  # Переходим на следующую ступень программы, файл выбран, можем его загрузить
            else:
                print(errors.Errors.file_select_error)
            if program_phase >= 1:
                file_status = check_file(selected_file)
                if file_status == 1:
                    main_list, info_line = fulfill_list(selected_file)
                    program_phase = 2  # Следующая стадия - файл загружен, есть валидный список
                    print(info_messages.InfoMessages.file_upload_success)
                elif file_status == 0:
                    print(errors.Errors.file_upload_error)
                    program_phase, main_list, info_line = try_to_fix_lines(selected_file)
                    if program_phase == 0:
                        continue
                else:
                    program_phase = 0
                    continue

            elif program_phase == 0:
                print(errors.Errors.chose_file_error)

        elif choice == 2:  # Получаем регион и колонку
            if program_phase >= 2:  # Если файл загружен, можем вводить регион и колонку
                region, column, program_phase = get_region_and_column(main_list, info_line)
                print(info_messages.InfoMessages.region_and_column_success)

            elif program_phase == 1:
                print(errors.Errors.upload_file_error)

            elif program_phase == 0:
                print(errors.Errors.chose_file_error)

            if program_phase >= 3:  # Если регион и колонка получены, кайф, переходим к подсчету метрик
                get_and_print_metrics(main_list, info_line, region, column)

            elif program_phase == 1:
                print(errors.Errors.upload_file_error)

            elif program_phase == 0:
                print(errors.Errors.chose_file_error)

            elif program_phase == 2:
                print(errors.Errors.chose_region_and_column_error)

        elif choice == 3:  # Выходим из программы
            print(info_messages.InfoMessages.exit_info)
            break


def ignore_bad_lines_and_fulfill_list(file_path):
    program_phase = 2
    min_columns = 3
    full_list_fixed = list()
    with open(file_path) as file:

        info_line = file.readline().strip().split(',')

        if not all(isinstance(column, str) for column in info_line):
            program_phase = 0
            main_list = None
            info_line = 0
            print(errors.Errors.file_upload_fix_error)
            return program_phase, main_list, info_line

        for line in file:
            line_element = line.strip().split(',')
            if len(line_element) < min_columns:
                continue
            if not line_element[0].isdigit() or line_element[0] == '':
                continue

            elif not isinstance(line_element[1], str) or line_element[1] == '':
                continue

            if not all(convert_to_int_or_float(value) != '' for value in line_element[2::]):
                continue

            line_list = [convert_to_int_or_float(value) for value in line_element]
            full_list_fixed.append(line_list)
    if len(full_list_fixed) < 2:
        print(errors.Errors.file_not_exhaustive)
        return None
    return program_phase, full_list_fixed, info_line


def try_to_fix_lines(file_path):
    while True:
        try:
            error_choice = int(input(info_messages.InfoMessages.file_upload_try_fix_info))
        except ValueError:
            print(errors.Errors.non_viable_number_error)
            continue
        if isinstance(error_choice, int) and (error_choice == 0 or error_choice == 1):
            if error_choice == 1:
                program_phase, main_list, info_line = ignore_bad_lines_and_fulfill_list(file_path)
                if program_phase == 0:
                    return program_phase, main_list, info_line
                else:
                    program_phase, main_list, info_line = ignore_bad_lines_and_fulfill_list(file_path)
                    print(info_messages.InfoMessages.file_upload_after_fix)
                    return program_phase, main_list, info_line

            if error_choice == 0:
                print(info_messages.InfoMessages.file_upload_no_fix)
                return None


def check_file(file_path):
    min_columns = 3
    acceptable_file_size_bytes = ACCEPTABLE_FILE_SIZE_MB * 1024 * 1024

    if os.path.getsize(file_path) == 0:
        print(errors.Errors.file_blank_error)
        return -1
    if os.path.getsize(file_path) > acceptable_file_size_bytes:
        print(errors.Errors.file_too_big_error)
        return -1
    try:
        with open(file_path) as file:

            info_line = file.readline().strip().split(',')  # info_line - самая важная проврека файла
            if len(info_line) < min_columns:
                print(errors.Errors.file_not_supported)
                return -1
            if not all(isinstance(column, str) for column in info_line):
                return 0

            for line in file:
                line_element = line.strip().split(',')
                if len(line_element) < min_columns:
                    return 0
                if not line_element[0].isdigit() or line_element[0] == '':
                    return 0
                elif not isinstance(line[1], str) or line_element[1] == '':
                    return 0
                elif not all(convert_to_int_or_float(value) != '' for value in line_element[2::]):
                    return 0
    except UnicodeDecodeError:
        print(errors.Errors.file_decode_error)
        return -1
    return 1


def convert_to_int_or_float(value):
    try:
        return int(value)
    except ValueError:
        try:
            return float(value)
        except ValueError:
            return value


def print_viable_regions(list):
    for number in range(len(list)):
        print(f"{number + 1}. {list[number]}")


def select_csv_file():
    file_path = filedialog.askopenfilename(
        initialdir="/Users/frogister/Documents/ЯПП/Lab1/Example files",
        title="Выберите CSV файл",
        filetypes=(("CSV файлы", "*.csv"), ("Все файлы", "*.*"))
    )
    return file_path


def fulfill_list(file_path):
    with open(file_path) as file:
        info_line = file.readline().strip().split(',')

        full_list = list()
        for line in file:
            line = line.split(',')
            line_list = [convert_to_int_or_float(value) for value in line]
            full_list.append(line_list)
    return full_list, info_line


def make_set_to_list(set):
    return list(set)


def print_viable_columns(line):
    for index in range(len(line)):
        if index > 1:
            print(f"{index - 1}. {line[index]}")
