#include <iostream>
#include <string>

// «Сложный» объект, создавать который со всеми параметрами неудобно
class Sandwich {
public:
	std::string bread;
	bool        toasted   = false;
	std::string filling;
	bool        mayo      = false;

	void describe() const {
		std::cout << bread << (toasted ? " toasted" : "")
				  << " with " << filling
				  << (mayo ? " + mayo" : "") << '\n';
	}
};

/* ---------- Builder ---------- */
class SandwichBuilder {
	Sandwich s_;
public:
	SandwichBuilder& bread(std::string b)   { s_.bread   = std::move(b); return *this; }
	SandwichBuilder& toasted(bool t = true) { s_.toasted = t;            return *this; }
	SandwichBuilder& filling(std::string f) { s_.filling = std::move(f); return *this; }
	SandwichBuilder& mayo(bool m = true)    { s_.mayo    = m;            return *this; }

	Sandwich build() { return std::move(s_); }
};

/* ---------- Клиентский код ---------- */
int main() {
	Sandwich blt = SandwichBuilder{}
			.bread("Baguette")
			.toasted()
			.filling("Bacon-Lettuce-Tomato")
			.mayo()
			.build();

	blt.describe();        // → Baguette toasted with Bacon-Lettuce-Tomato + mayo
}
