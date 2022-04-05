int main() {
    int a = 0;
    {
        {
            int a = 2;
        }
    }
    return a;
}