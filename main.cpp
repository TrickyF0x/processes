#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <algorithm>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
 
std::string spath() // ЧТЕНИЕ ИМЕНИ ФАЙЛА
{
	std::string pth;
	std::cout << "Enter path to directory: ";
	std::getline(std::cin, pth);
	return pth;
}

int main()
{
	//инициализация вектора
    std::string path = spath();
    auto it = fs::directory_iterator(path);
    std::vector<fs::path> array;
    std::copy_if(fs::begin(it), fs::end(it), std::back_inserter(array), 
    [](const auto& entry) 
    {
        return fs::is_regular_file(entry);
    });

    //запись списка в файл
    std::string filename = "./list.txt";
    std::fstream stream(filename, stream.trunc | stream.in | stream.out);
    if (!stream.is_open()) 
    {
        std::cout << "Не удалось открыть файл " << filename << std::endl;
    } 
    else 
    {
        for (auto & p : array)
            stream << p.string() << std::endl;
    }	

	std::string s; // сюда будем класть считанные строки
	std::ifstream file("./list.txt"); // файл из которого читаем
	while(getline(file, s))
	{
	pid_t pr;
	pr = fork();
	int status;
	if(pr == 0)
	{
		execl("controlsum", " ", s.c_str(), NULL);
	}
	else if (pr > 0)
	{
		wait(&status);
	}

	}

    return 0;
}