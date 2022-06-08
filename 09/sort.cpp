#include "sort.hpp"

void insertion_sort(std::vector<uint64_t> &chunc)
{
    for(uint64_t j = 1; j < chunc.size(); j++){
        uint64_t key = chunc[j];
        int i = j - 1;
        while(i >= 0 && chunc[i] > key){
          chunc[i + 1] = chunc[i];
          i = i - 1;
          chunc[i + 1] = key;
        }
    }
}

void split_into_files(
                      const std::string filename,
                      const std::string f1,
                      const std::string f2,
                      const size_t limit
                     )
{
    std::fstream data(filename, std::ios::in | std::ios::binary);
	std::fstream stream_1(f1, std::ios::out | std::ios::binary);
	std::fstream stream_2(f2, std::ios::out | std::ios::binary);
    
	const size_t type_size = sizeof(uint64_t);
    const uint64_t chunk_num = fs::file_size(filename) / limit;
	const uint64_t additional = fs::file_size(filename) % limit == 0 ? 0 : 1;
    
    std::vector<uint64_t> chunk(limit / type_size);
	for (uint64_t i = 0; i < chunk_num + additional; ++i) {
		data.read((char *) chunk.data(), limit);
        if (i < chunk_num / 2) {
            stream_1.write((char *) chunk.data(), chunk.size() * sizeof chunk[0]);
        } else {
            stream_2.write((char *) chunk.data(), chunk.size() * sizeof chunk[0]);
        }
	}
    
    data.close();
    stream_1.close();
    stream_2.close();
}

void merge_and_sort(
                    std::fstream &f,
                    std::vector<uint64_t> &chunk,
                    uint64_t pos,
                    uint64_t size,
                    uint64_t offset = 0
                    )
{
    f.seekg(pos);
    f.read((char *) (chunk.data() + offset), size);
    insertion_sort(chunk);
    f.seekp(pos);
    f.write((char *) (chunk.data() + offset), size);
}

void sort(const std::string filename, const size_t limit)
{
	size_t type_size = sizeof(uint64_t);
	std::fstream file(filename, std::ios::out | std::ios::in | std::ios::binary);
	size_t chunk_num = fs::file_size(filename) / limit;
	size_t additional = fs::file_size(filename) % limit == 0 ? 0 : 1;
    size_t offset = limit / type_size / 2;

	std::vector<uint64_t> chunk(limit / type_size);
	for (uint64_t i = 0; i < chunk_num + additional; ++i) {
        merge_and_sort(file, chunk, limit * i, limit);
	}

    for (int64_t i = chunk_num; i > 0; --i) {
        
		file.seekp(limit / 2 * (chunk_num - i));
		file.read((char *) chunk.data(), limit / 2);
        
		for (int64_t j = 1; j < i; ++j) {
            size_t pos = limit / 2 * (chunk_num - i) + limit * j;
            merge_and_sort(file, chunk, pos, limit / 2, offset);
		}
        
        size_t pos_i = limit / 2 * (chunk_num - i) + limit * i - limit / 2;
        
		file.seekp(limit / 2 * (chunk_num - i));
		file.write((char *) chunk.data(), limit / 2);
		file.seekp(pos_i);
		file.read((char *) (chunk.data() + offset), limit / 2);
        
		for (int64_t j = i - 2; j >= 0; --j) {
            size_t pos = limit / 2 * (chunk_num - i + 1) + limit * j;
            merge_and_sort(file, chunk, pos, limit / 2);
		}
		file.seekg(pos_i);
		file.write((char *) (chunk.data() + offset), limit / 2);
		for (int64_t j = 0; j < i - 1; ++j) {
            size_t pos = limit / 2 * (chunk_num - i + 1) + limit * j;
            merge_and_sort(file, chunk, pos, limit);
		}
	}
    
    file.close();
}

void merge_two_files(
                    const std::string f1,
                    const std::string f2,
                    const std::string res_name
                    )
{
	const size_t type_size = sizeof(uint64_t);
	std::fstream stream_1(f1, std::ios::in | std::ios::binary);
	std::fstream stream_2(f2, std::ios::in | std::ios::binary);
	std::fstream out_stream(res_name, std::ios::out | std::ios::binary);
    const uint64_t f1_size = fs::file_size(f1) / 8, f2_size = fs::file_size(f2) / 8;

    int64_t x, y;
    stream_1.read((char*)& x, type_size);
    stream_2.read((char*)& y, type_size);
    
    uint64_t i = 1, j = 1;
    
    while ((i < f1_size + 1) && (j < f2_size + 1)) {
        if (x < y) {
            out_stream.write((char*) &x, type_size);
            if (++i < f1_size + 1) stream_1.read((char*) &x, type_size);
        } else {
            out_stream.write((char*) &y, type_size);
            if (++j < f2_size + 1) stream_2.read((char*) &y, type_size);
        }
    }

    while (i++ < f1_size + 1) {
        out_stream.write((char*) &x, type_size);
        if (i < f1_size + 1) stream_1.read((char*) &x, type_size);
    }

    while (j++ < f2_size + 1) {
        out_stream.write((char*) &y, type_size);
        if (j < f2_size + 1) stream_2.read((char*) &y, type_size);
    }
    
    stream_1.close();
    stream_2.close();
    out_stream.close();
}

void threads_sort(
                const std::string filename,
                size_t limit,
                const std::string res_name = "result.bin"
                )
{
	split_into_files(filename, "ex1.bin", "ex2.bin", limit);
    std::thread thr1(sort, "ex1.bin", limit / 2);
    std::thread thr2(sort, "ex2.bin", limit / 2);

    thr1.join();
    thr2.join();
    
    merge_two_files("ex1.bin", "ex2.bin", res_name);
}