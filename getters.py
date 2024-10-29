import numpy as np
from tabulate import tabulate

import errors
import info_messages
from logic import make_set_to_list, print_viable_regions, print_viable_columns
from metrics_class import Metrics


def get_and_print_metrics(main_list, info_line, region, column):
    region_list = get_region_list(main_list, region)
    table_region_list = tabulate(region_list, headers=info_line, tablefmt="rounded_grid")
    print(f"Таблица значений по заданному региону:\n{table_region_list}\n")
    metrics_list = get_column_metrics_list(region_list, column)
    metrics = Metrics(get_max_metrics(metrics_list), get_min_metrics(metrics_list), get_mean_metrics(metrics_list),
                      get_med_metrics(metrics_list))
    list_to_print = [
        ["Метрики", "Значения"],
        ["Максимум:", metrics.max],
        ["Минимум:", metrics.min],
        ["Ср. арифм.:", metrics.mean],
        ["Медиана", metrics.med]
    ]
    table_metrics = tabulate(list_to_print, headers="firstrow", tablefmt="rounded_grid")
    print(f"Метрики и значения по выбранному региону и колонке:\n{table_metrics}\n")
    percentiles = np.arange(0, 101, 5)
    percentiles_values = np.percentile(metrics_list, percentiles)

    list_percentiles = list(zip(percentiles, percentiles_values))
    table_percentiles = tabulate(list_percentiles, headers=["Перцентиль", "Значения"], tablefmt="rounded_grid")
    print(f"Таблица перцентилей:\n{table_percentiles}\n")


def get_region_list(list, region):
    region_list = [line for line in list if line[1] == region]
    return region_list


def get_and_sort_regions_list(list):
    region_set = get_viable_regions(list)
    region_list = make_set_to_list(region_set)
    sorted_region_list = sorted(region_list)
    return sorted_region_list


def get_list_all_metrics_one_region(list, region):
    correct_region_list = list()
    for correct_list in list:
        if correct_list[1] == region:
            correct_region_list.append(correct_list)
    return correct_region_list


def get_column_metrics_list(region_list, column):
    column_metrics_list = [line[column] for line in region_list]
    return column_metrics_list


def get_max_metrics(metrics_list):
    return max(metrics_list)


def get_min_metrics(metrics_list):
    return min(metrics_list)


def get_mean_metrics(metrics_list):
    return np.mean(metrics_list)


def get_med_metrics(metrics_list):
    return np.median(metrics_list)


def get_region(list):
    sorted_region_list = get_and_sort_regions_list(list)
    while True:
        print_viable_regions(sorted_region_list)
        region_number = get_viable_int_number(get_region_list_length(sorted_region_list),
                                              info_messages.InfoMessages.chose_region_recommendation)
        if region_number != 0:
            return sorted_region_list[region_number - 1]


def get_column(info_line):
    while True:
        print_viable_columns(info_line)
        viable_column_number = get_viable_number_of_columns(info_line)
        column = get_viable_int_number(viable_column_number,
                                       info_messages.InfoMessages.chose_column_recommendation)
        if column != 0:
            return column


def get_region_and_column(list, info_line):
    region = get_region(list)
    column = get_column(info_line) + 1  # + 1, так как первые 0 и 1 - year и region
    program_phase = 3
    return region, column, program_phase


def get_viable_regions(list):
    region_set = set()
    for line in list:
        region_set.add(line[1])
    return region_set


def get_region_list_length(list):
    return len(list)


def get_viable_number_of_columns(info_line):
    viable_number_of_columns = 0
    for number in info_line:
        viable_number_of_columns += 1
    return viable_number_of_columns - 2  # Получается без двух первых колонок


def get_viable_int_number(number_of_viable_options, info_text):
    option = input(info_text)
    try:
        correct_option = int(option)
        if correct_option <= 0 or correct_option > number_of_viable_options:
            print(errors.Errors.non_viable_number_error)
            return 0
    except ValueError:
        print(errors.Errors.non_integer_input_error)
        return 0
    return correct_option
