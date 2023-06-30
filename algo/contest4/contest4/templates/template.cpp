#include <iostream>
#include <fstream>

using namespace std;

// Необходимо вернуть вектор ans, который содержит три элемента:
// ans[0] - вес найденного самоцвета красного цвета
// ans[1] - вес найденного самоцвета зеленого цвета
// ans[2] - вес найденного самоцвета синего цвета
int* solve(int nr, int ng, int nb, int* r, int* g, int* b)
{
   int* ans = new int[3];

   // Your solution here

   return ans;
}

int main() {
   fstream fin;
   fstream fout;
   fin.open("input.txt",ios::in);
   fout.open("output.txt",ios::out);

   if(fin.is_open()) {
       int t;
       fin >> t;
       while (t--) {
           int nr, ng, nb;
           fin >> nr >> ng >> nb;

           int* r = new int[nr];
           int* g = new int[ng];
           int* b = new int[nb];
           for (int i = 0; i < nr; ++i)
               fin >> r[i];
           for (int i = 0; i < ng; ++i)
               fin >> g[i];
           for (int i = 0; i < nb; ++i)
               fin >> b[i];

           int* ans = solve(nr, ng, nb, r, g, b);

           fout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << endl;

           delete[] r;
           delete[] g;
           delete[] b;
           delete[] ans;
       }
   }
   fin.close();
   fout.close();
   return 0;
}
