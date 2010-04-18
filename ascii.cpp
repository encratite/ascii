#include <iostream>
#include <nil/file.hpp>
#include <nil/string.hpp>

int main(int argc, char ** argv)
{
	if(argc != 5)
	{
		std::cout << argv[0] << " <raw 8-bit input data> <width> <height> <ASCII output file>" << std::endl;
		return 1;
	}
	std::string data;
	if(!nil::read_file(argv[1], data))
	{
		std::cout << "Unable to read input" << std::endl;
		return 1;
	}
	long width, height;
	if(!nil::string::string_to_number<long>(argv[2], width) || !nil::string::string_to_number<long>(argv[3], height))
	{
		std::cout << "Unable to parse dimensions" << std::endl;
		return 1;
	}
	std::string bytes = "\xdb\xb2\xb1\xb0 ";
	std::size_t divisor = 256 / bytes.size() + 1;
	std::stringstream output;
	std::size_t spaces = 0;
	for(long y = 0; y < height; y++)
	{
		for(long x = 0; x < width; x++)
		{
			ulong byte_value = static_cast<unsigned char>(data[y * width + x]);
			char byte = bytes[byte_value / divisor];
			if(byte == ' ')
				spaces++;
			else
			{
				if(spaces > 0)
				{
					output << std::string(spaces, ' ');
					spaces = 0;
				}
				output << byte;
			}
		}
		output << "\r\n";
		spaces = 0;
	}
	std::string content = output.str();
	std::cout << content;
	nil::write_file(argv[4], content);
	return 0;
}