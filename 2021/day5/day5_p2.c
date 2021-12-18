/* Again, I got help from another video for this problem as I found it diffucult:
 * https://www.youtube.com/watch?v=pEThv-wedZM
 * */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INPUT 1000

struct vector {
	int x, y;
};

struct line2d {
	struct vector start, end;
};

bool readinput(char *filename, struct line2d *lines,
		int *linecount) 
{
	FILE *file = fopen(filename, "r");
	if (file == 0)
	{
		printf("Could not open file");
		return false;
	}

	struct line2d input_lines[INPUT];
	*linecount = 0;
	while(fscanf(file, "%d,%d -> %d,%d", 
				&lines[*linecount].start.x,
				&lines[*linecount].start.y,
				&lines[*linecount].end.x,
				&lines[*linecount].end.y))
	{
		*linecount += 1;
		if (feof(file))
		{
			break;
		}
	}

	fclose(file);
	return true;
};

int main() {
	struct line2d lines[INPUT];
	int linecount;
	if (readinput("input.txt", lines, &linecount))
	{

		int map_width = 0;
		int map_height = 0;
		for (int line_i = 0; line_i < linecount; line_i++)
		{
			struct line2d line = lines[line_i];
			if (line.start.x > map_width)
			{
				map_width = line.start.x;
			}
			if (line.end.x > map_width)
			{
				map_width = line.end.x;
			}
			if (line.start.y > map_height)
			{
				map_height = line.start.y;
			}
			if (line.end.y > map_height)
			{
				map_height = line.end.y;
			}
		};
		
		map_width++;
		map_height++;
		int *map = (int*)calloc(map_width * map_height, sizeof(int));

		for (int line_i = 0; line_i < linecount; line_i++)
		{
			struct line2d line = lines[line_i];
			struct vector cursor = line.start;
			bool end = false;
			while(!end)
			{
				end = ((cursor.x == line.end.x) && (cursor.y == line.end.y));

				int map_i = cursor.x + (cursor.y * map_width);
				map[map_i]++;
				if (cursor.x < line.end.x)
				{
					cursor.x++;
				} else if (cursor.x > line.end.x)
				{
					cursor.x--;
				}
				if (cursor.y < line.end.y)
				{
					cursor.y++;
				}
				else if (cursor.y > line.end.y)
				{
					cursor.y--;
				}
			}
		}
		printf("MAP: \n");
		for (int y = 0; y < map_width; y++)
		{
			for (int x = 0; x < map_width; x++)
			{
				int map_i = x + (y * map_width);
				if (map[map_i] == 0)
				{
					printf(".");
				}
				else
				{
					printf("%d", map[map_i]);
				}
			}
			printf("\n");
		}
		int overlapping_cells = 0;
		for (int map_i; map_i < (map_width * map_height); map_i++)
		{
			if (map[map_i] >= 2) {
				overlapping_cells++;
			}
		}
		free(map);

		printf("%d\n", overlapping_cells);
	}

}
