#include "Books.cpp"


using namespace std;
const int FILE_HEADER_SIZE = sizeof(int);
int main() {
    vector<Book*> demoBooks = {
        new Book("s0055","t1","0055"),
        new Book("s0065","t2","0065"),
        new Book("s0075","t3","0075"),
        new Book("s0095","t4","0095"),
        new Book("s519","t5","519"),
        new Book("s518","t6","518"),
    };
    BooksManager* bookManager = new BooksManager();
    for(auto b: demoBooks){
        bookManager->saveBookToFileWithDelimiter(*b);
    }
    bookManager->updateName("s0065","ahmedsss");
    bookManager->updateName("s0095","tolb");
    bookManager->deleteBook("s0055");
    delete bookManager;
    return 0;
}
