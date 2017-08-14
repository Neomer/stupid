#ifndef SINGLETON
#define SINGLETON

template <class C>
class C {
public:
	static C& instance()
    {
        static C s;
        return s;
    }
	
private:
	C();
	~C();
	C(C const&); 
	C& operator= (C const&); 

};

#endif // SINGLETON

