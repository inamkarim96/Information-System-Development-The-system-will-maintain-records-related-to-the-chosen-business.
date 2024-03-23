
#include <iostream>
#include <fstream>
#include <string> 

struct record {
    int id;
    char name[50];
    double price;
    bool isvalid;
};

void save_record(const record R[], int count) {
    std::ofstream file("record.bin", std::ios::binary);
    if (file.is_open()) {
        for (int i = 0; i < count; i++) {
                file.write((char*)&R[i], sizeof(record));
        }
        file.close();
        std::cout << "Records written to file.\n";
      
    }
    else {
        std::cout << "Unable to open file for writing.\n";
    }
}

void add_record(record R[], int& count) {
   
    std::cout << "Enter book_id: ";
    std::cin >> R[count].id;
  
    for (int i = 0; i < count; i++) {
        if (R[i].id == R[count].id) {
            std::cout << "Record with this ID already exists\n";
            return;
        }
    }
    std::cout << "Enter book name: ";
    std::cin.ignore();
    std::cin.getline(R[count].name, sizeof(R[count].name));
    std::cout << "Enter price: ";
    std::cin >> R[count].price;
    count++;
}

void delete_record(record R[], int& count, int id) {
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (R[i].id == id) {
            R[i].isvalid = false;
            found = true;
            std::cout << "Record deleted with ID: " << id << std::endl;
            std::cout << "ID: " << R[i].id << std::endl;
            std::cout << "book: " << R[i].name << std::endl;
            std::cout << "Price: " << R[i].price << std::endl;
            break;
        }
    }
    if (!found) {
        std::cout << "No record found for ID: " << id << std::endl;
    }
}

void search_record(record R[], int count, int id) {
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (R[i].id == id && R[i].isvalid) {
            found = true;
            std::cout << "Record found\n";
            std::cout << "ID: " << R[i].id << std::endl;
            std::cout << "book: " << R[i].name << std::endl;
            std::cout << "Price: " << R[i].price << std::endl;
            
            break;
        }
    }
    if (!found) {
        std::cout << "No record found for ID: " << id << std::endl;
    }
}

void read_record(record R[], int& count) {
    std::ifstream file("record.bin", std::ios::binary);
    if (file.is_open()) {
        count = 0;
        while (file.good()) {
            file.read((char*)&R[count], sizeof(record));
                count++;
        }
        file.close();
    }
    else {
        std::cout << "File not found\n";
    }
}

void export_record(record R[], int count, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file for export.\n";
        return;
    }
    for (int i = 0; i < count; i++) {
            file.write((char*)&R[i], sizeof(record));
    }
    file.close();
    std::cout << "Records exported.\n";
}

void import_record(record R[], int& count, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        while (file.good()) {
            file.read((char*)&R[count], sizeof(record));
            count++;
        }
        file.close();
        std::cout << "Records imported.\n";
    }
    else {
        std::cout << "Failed to open file for import.\n";
    }
}

int main(int argc, char* argv[]) {
    const int maxrecord = 100;
    record R[maxrecord];
    int count = 0;

    if (argc < 2 || argc > 3) {
        std::cout << "\n_________welcome to bookstore__________\nUsage: " << argv[0] << "[help | add | delete | search | import | export] [filename]\n";
        return 1;
    }

    read_record(R, count);

    std::string arg(argv[1]);
    if (arg == "help") {
        std::cout << "add: Add a new record.\n";
        std::cout << "delete[id]: Delete a record with the ID.\n";
        std::cout << "search[id] : Search for a record with the ID.\n";
        std::cout << "import [filename]: Import records from a file.\n";
        std::cout << "export[filename] : Export records to a file.\n";
    }

    else if (arg == "import" || arg == "export") {
        std::string filename(argv[2]);
        if (arg == "import")
            import_record(R, count, filename);
        else
            export_record(R, count, filename);
    }
    else if (arg == "add") {
        add_record(R, count);
    }
    else if (arg == "delete") {
        int id = std::stoi(argv[2]);
        delete_record(R, count, id);
    }
    else if (arg == "search") {
        int id = std::stoi(argv[2]);
        search_record(R, count, id);
    }
    else {
        std::cout << "Invalid command\n";
        return 1;
    }

    save_record(R, count); // Save records to the binary file after processing command line arguments

    return 0;
}
