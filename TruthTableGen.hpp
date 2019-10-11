#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>

#define T 1
#define F 0

class TxtTableGen
{
private:
	std::vector<std::vector<std::string>> p;
	std::vector<int> len;
	int size_x   = 0;
	int size_y   = 0;
	int h_offset = 0;
	std::string v_separator;
	std::string h_separator;
	std::string border;
	std::string out;
	std::string offset;
	int width       = 0;
	int actual_line = 0;

	void gen_v_separator_line()
	{
		out += offset + border;
		for (int i = 0; i < width; i++) out += v_separator;
		out += border + "\n";
	}

	void get_width()
	{
		width = 0;
		for (int i = 0; i < size_x; i++)
			width += len[i] + 1;
		width--;
	}

	void get_offset()
	{
		offset = "";
		for (int i = 0; i < h_offset; i++)
			offset += " ";
	}

	int get_matrix_size()
	{
		int status = 0;
		if (p.size() > 0) {
			int previous = p[0].size();
			size_y = p.size();
			for (int y = 1; y < size_y; y++) {
				int buffer = p[y].size();
				if (buffer != previous) {
					status = -1;
					break;
				}
			}
			if (status != -1)
				size_x = previous;
		} else {
			status = -1;
		}
		return status;
	}

	void get_len()
	{
		for (int x = 0; x < size_x; x++) {
			int major = 0;
			for (int y = 0; y < size_y; y++) {
				int tmp = p[y][x].length();
				if (tmp > major)
					major = tmp; 
			}
			len.push_back(major);
		}
	}

	int gen_line() 
	{
		int status = 0;
		if (actual_line < size_y) {
			out += offset + border;
			for (int x = 0; x < size_x - 1; x++) {
				out += p[actual_line][x];
				for (int i = p[actual_line][x].length(); 
				i < len[x]; i++) out += ' ';
				out += h_separator;
			}
			out += p[actual_line][size_x - 1];
			for (int i = p[actual_line][size_x - 1].length();
			i < len[size_x - 1]; i++) out += ' ';
			out += border + "\n";
			actual_line++;
		} else {
			status = -1;
		}
		return status;
	}

public:

	TxtTableGen(int h_offset, std::string v_separator, std::string h_separator,
	std::string border)
	{
		this->h_offset = h_offset;
		this->v_separator = v_separator;
		this->h_separator = h_separator;
		this->border = border;
	}

	void add_line(std::vector<std::string> line)
	{
		p.push_back(line);
	}

	std::string generate()
	{
		if (get_matrix_size() != -1) {
			get_len();
			get_width();
			get_offset();
			gen_v_separator_line();
			gen_line();
			gen_v_separator_line();
			int s = gen_line();
			while (s != -1)
				s = gen_line();
			gen_v_separator_line();
		}
		return out;
	}
};

typedef bool (*BooleanFunction)(std::vector<bool>);

class TruthTableGen
{
private:
	const std::vector<std::string> vars = {"x","y","z","w"};
	const std::vector<std::vector<std::vector<bool>>> min  =
	{
		{	
			{F},
			{T}
		},
		{	
			{F,F},
			{F,T},
			{T,F},
			{T,T}
		},
		{	
			{F,F,F},
			{F,F,T},
			{F,T,F},
			{F,T,T},
			{T,F,F},
			{T,F,T},
			{T,T,F},
			{T,T,T}
		},
		{	
			{F,F,F,F},
			{F,F,F,T},
			{F,F,T,F},
			{F,F,T,T},
			{F,T,F,F},
			{F,T,F,T},
			{F,T,T,F},
			{F,T,T,T},
			{T,F,F,F},
			{T,F,F,T},
			{T,F,T,F},
			{T,F,T,T},
			{T,T,F,F},
			{T,T,F,T},
			{T,T,T,F},
			{T,T,T,T}
		},
	};
	std::vector<std::string> func_names;
	std::vector<BooleanFunction> funcs;
	int func_qnt = 0;
	int var_qnt = 0;

	std::string bool_array_to_bin(std::vector<bool> b)
	{
		std::string tmp;
		for (int i = 0; i < b.size() - 1; i++)
			tmp += ((b[i] == T)? "1 " : "0 ");
		if ((b.size() - 1) >= 0)
			tmp += ((b[b.size() - 1] == T)? "1" : "0");
		return tmp;
	}

	std::string bool_array_to_min(std::vector<bool> b)
	{
		std::string tmp;
		const std::vector<std::string> letters = {"x","y","z","w"};
		for (int i = 0; i < b.size(); i++) {
			tmp += ((b[i] == F)? "~" : " " );
			tmp += letters[i];
		}
		return tmp;
	}

	bool exec_func(int index, std::vector<bool> in)
	{
		return funcs[index](in); 
	} 
public:
	TruthTableGen(std::vector<BooleanFunction> funcs, 
	std::vector<std::string> func_names, int var_qnt)
	{
		this->funcs = funcs;
		this->func_names = func_names;
		this->var_qnt = var_qnt;
		func_qnt = funcs.size();
	}

	std::string generate()
	{
		TxtTableGen table(0,"-","|","||");
		std::string tmp;
		switch (var_qnt)
		{
		case 1:
			tmp = "x";
			break;
		case 2:
			tmp = "x y";
			break;
		case 3:
			tmp = "x y z";
			break;
		case 4:
			tmp = "x y z w";
			break;
		default:
			break;
		}
		std::vector<std::string> header = {"#mintermos","mintermos",tmp};
		for (int i = 0; i < func_qnt; i++)
			header.push_back(func_names[i]);
		table.add_line(header);
		int pw = pow(2,var_qnt);
		for (int i = 0; i < pw; i++) {
			std::vector<std::string> line = {
				std::to_string(i),
				bool_array_to_min(min[var_qnt - 1][i]),
				bool_array_to_bin(min[var_qnt - 1][i])
			};
			for (int j = 0; j < func_qnt; j++) {
				line.push_back(
				std::to_string(exec_func(j,min[var_qnt - 1][i]))
				);
			}
			table.add_line(line);
		}
		return table.generate();
	}
};


