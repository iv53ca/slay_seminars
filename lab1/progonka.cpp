#include <iostream>
#include <vector>
class matrix{
private:
    double **a;
    int n,m;
public:
    matrix (){
        a = 0;
        n = 0;
        m = 0;
    }
    matrix (int N, bool E = 0){
        n = N;
        m = N;
        a = new double *[n];
        for (int i = 0; i < n; ++ i){
            a[i] = new double[m];
            for(int j = 0; j < m; ++ j){
                a[i][j] = (i == j)*E;
            }
        }

    }
    matrix (double nums[], int N){
        n = N;
        m = 1;
        a = new double *[n];
        for (int i = 0; i < n; i++){
            a[i] = new double[1];
            a[i][0] = nums[i];
        }
    }
    int N (){
        return n;
    }
    int M (){
        return m;
    }
    double* operator [] (int index){
        return this->a[index];
    }
    matrix scanMatrix (){
        int n;
        std::cin >> n;
        matrix a = matrix(n);
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < n; ++ j)
                std::cin >> a[i][j];
        return a;
    }
    matrix diag3Matrix(int N, std::vector <double> mass_of_numb){
        n = N;
        if(mass_of_numb.size() == 3*n - 2){
            matrix a = matrix(n);
            a[0][0] = mass_of_numb[0];
            a[0][1] = mass_of_numb[1];
            a[n-1][n-2] = mass_of_numb[3*n - 4];
            a[n-1][n-1] = mass_of_numb[3*n - 3];
            for(int i = 1; i < n-1; i++){
                for(int j = 0; j < n; j++){
                    if(i == j)
                        a[i][j] = mass_of_numb[3*i];
                    if(i == j+1)
                        a[i][j] = mass_of_numb[3*i-1];
                    if(i == j-1)
                        a[i][j] = mass_of_numb[3*i+1];
                }
            }
            return a;
        }
        else{
            return 0;
        }
    }
    void printMatrix (matrix a)
    {
        for (int i = 0; i < a.N (); ++ i)
        {
            for (int j = 0; j < a.M (); ++ j)
                std::cout << a[i][j];
            std::cout << std::endl;
        }
    }

};
int main(){
    int n;
    std::cin >> n;
    std::vector <double> nums(3*n - 2);
    for(int i = 0; i < 3*n - 2; i++){
        std::cin >> nums[i];
    }
    double vals[n];
    for(int i = 0; i < n; i++){
        std::cin >> vals[i];
    }
    matrix coeffs;
    coeffs = coeffs.diag3Matrix(n, nums);
    matrix values = matrix(vals, n);
    std::vector <double> p(n - 1);
    std::vector <double> q(n - 1);
    q[0] = values[0][0]/coeffs[0][0];
    p[0] = (-1)*coeffs[0][1]/coeffs[0][0];
    for(int i = 1; i < n-1; i++){
        int ib = i;
        int ia = ib;
        int ic = ib;
        p[i] = (-1)*coeffs[ic][ic+1]/(coeffs[ia][ia-1]*p[i-1] + coeffs[ib][ib]);
        q[i] = (values[i][0] - coeffs[ia][ia-1]*q[i-1])/(coeffs[ia][ia-1]*p[i-1] + coeffs[ib][ib]);
    }
    std::cout<<p[0]<<" "<<p[1]<<" "<<q[0]<<" "<<q[1]<<std::endl;
    std::vector <double> sol(n);
    sol[n-1] = (values[n-1][0] - coeffs[n-1][n-2]*q[n-2])/(coeffs[n-1][n-2]*p[n-2] + coeffs[n-1][n-1]);
    for(int i = n-1; i > 0; --i){
        sol[i-1] = p[i-1]*sol[i] + q[i-1];
    }
    for(int i = 0; i < n; i++){
        std::cout << "x" << i << " = " << sol[i] << std::endl;
    }
    return 0;
}
