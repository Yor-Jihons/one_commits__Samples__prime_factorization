#include<iostream>
#include<vector>
#include<sstream>
#include<algorithm>
#include<memory>
#include<limits>

using namespace std;

namespace Util{
    /** @brief The array of the strings. */
    using StrVec = std::vector<std::string>;

    /**
     * @brief Separate the strings.
     * @param text The string you want to separate.
     * @param delim The delim string. ( def: " " )
     * @return The object of the std::Vector for std::string, which was separated.
    */
    StrVec split( const std::string& text, const std::string& delim = std::string(" ") ){
        StrVec res;
        int end = 0, begin = 0, n = 0;
        while( true ){
            end   = text.find( delim, begin );
            if( end == std::string::npos ){
                res.push_back( text.substr( begin, (text.size() - begin) ) );
                break;
            }
            n = (end - begin);
            res.push_back( text.substr( begin, n ) );
            begin = end + 1;
        }
    return res;
    }

    /**
     * @brief Convert the data to the string.
     * @param val The data you want to convert.
     * @return The string which was converted from the data.
     */
    template<typename T> std::string ToString( T val ){
        std::stringstream ss;
        ss << val << flush;
    return ss.str();
    }
}


namespace Original{
    class Prime{
        public:
            Prime( int size ) : prime_(Prime::CreatePrimesWithSieveofEratosthenes(size)){}
            ~Prime() = default;

            int CalcFitPrime( int n ){
                for( int i = 0; i < static_cast<int>(prime_.size()); i++ ){
                    if( n % prime_[i] == 0 ) return prime_[i];
                }
            return -1;
            }

            void Print( void ){
                for( int i = 0; i < prime_.size(); i++ ){
                    cout << prime_[i] << " " << flush;
                }
                cout << endl;
            }
        protected:
            /**
            * @brief Enumerate the primes with Sieve of Eratosthenes.
            * @param size The max number.
            * @return The primes.
            */
            static std::vector<int> CreatePrimesWithSieveofEratosthenes( int size ){
                std::vector<bool> nums( size, true );
                nums[0] = false;

                for( int i = 2; i < size; i++ ){
                    if( !nums[i] ) continue;

                    for( int j = i * 2; j < size; j = j * 2 ){
                        nums[j] = false;
                    }
                }
                std::vector<int> prime;
                for( int i = 2; i < size; i++ ){
                    if( nums[i] ) prime.push_back( i );
                }
            return prime;
            }
        private:
            std::vector<int> prime_;
    };
}

namespace Original{
    class Power{
        public:
            Power( int n ) : n_(n),counter_(1){}
            ~Power() = default;

            bool IsMatch( int n ){
                return (n == n_ ? true : false);
            }

            void Count( void ){
                counter_++;
            }

            std::string ToString( void ) const{
                std::stringstream ss;
                ss << n_;
                if( counter_ > 1 ) ss << "^" << counter_;
            return ss.str();
            }
        private:
            int n_;
            int counter_;
    };

    class PowerManager{
        public:
            PowerManager(){}
            ~PowerManager() = default;

            void Count( int n ){
                bool isAlreadyExisted = false;
                for( int i = 0; i < static_cast<int>(powers.size()); i++ ){
                    if( powers[i].IsMatch( n ) ){
                        powers[i].Count();
                        isAlreadyExisted = true;
                        break;
                    }
                }

                if( !isAlreadyExisted ) powers.push_back( Power( n ) );
            }

            void Print( void ) const{
                for( int i = 0; i < static_cast<int>(powers.size()); i++ ){
                    cout << powers[i].ToString() << flush;
                    if( i != static_cast<int>(powers.size()) - 1 ){
                        cout << " " << flush;
                    }
                }
                cout << endl;
            }
        private:
            std::vector<Original::Power> powers;
    };
}


int main( int argc, char** argv ){
    int n;
    cin >> n;

    Original::Prime prime( n );
    std::vector<int> nums;

    while( true ){
        int p = prime.CalcFitPrime( n );
        if( p == n ){
            nums.push_back( p );
            break;
        }
        n /= p;
        nums.push_back( p );
    }

    std::sort( nums.begin(),nums.end() );

    Original::PowerManager powerManager;

    for( int i = 0; i < static_cast<int>(nums.size()); i++ ){
        powerManager.Count( nums[i] );
    }

    powerManager.Print();
return 0;
}
