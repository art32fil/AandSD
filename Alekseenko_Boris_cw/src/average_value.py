
def av_val(name):
    av_data = []
    save = name
    for i in range(0, 201, 1):
        name = name + str(i) + '.txt'
        file = open(name, 'r')
        data = file.read()
        data = list(data.split())

        name = save

        a = 0
        for y in range(1, len(data)):
            a += int(data[y])

        average = a / len(data)
        av_data.append(average)
        file.close()

    return av_data


def print_into_file(data, a):
    name = "data_"

    arr = [1]
    for i in range(50, 10050, 50):
        arr.append(i)
    name = name + str(a) + '.txt'
    f = open(name, 'w')
    for j in range(0, len(data)):
        f.write(str(arr[j]) + " " + str(data[j]) + '\n')
    f.close()


name_d_a = 'result_d_a/result_a_'
name_d_w = 'result_d_w/result_w_'
name_i_a = 'result_i_a/result_a_'
name_i_w = 'result_i_w/result_w_'

av_data_d_a = av_val(name_d_a)
av_data_d_w = av_val(name_d_w)
av_data_i_a = av_val(name_i_a)
av_data_i_w = av_val(name_i_w)


print_into_file(av_data_d_a, 0)
print_into_file(av_data_d_w, 1)
print_into_file(av_data_i_a, 2)
print_into_file(av_data_i_w, 3)
