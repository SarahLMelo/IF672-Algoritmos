#include <iostream>

int main(){
    long long int a, b, ans = 0;
    std::cin >> a >> b;

    while(b--) ans += a;

    std::cout << ans << std::endl;

    return 0;
}