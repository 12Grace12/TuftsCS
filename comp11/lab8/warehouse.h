//
// Definition of an Warehouse Class
//  A Warehouse keeps a list of quantities of a set of products.
//  There are NUM_PRODUCTS in the business, each product has a product number
//  in the range 0 to NUM_PRODUCTS - 1
//  
//  The operations on can perform on an warehouse are
//  a. create a new warehouse one (with an initial quantity for all)
//  b. restock warehouse - globabally or for specific items
//  c. Ask the warehouse if a product is in stock
//  d. Ask the warehouse how many of a given product are on hand
//  e. sell items (i.e. decrement the count for that item)
//  f. return a list of all items with quantity below a certain value
//

const int NUM_PRODUCTS = 10;

class Warehouse
{
	public:
		// Two constructors, one sets all product quantities to zero
		Warehouse();
		//   the other sets all product quantities to a specfied qty
		Warehouse(int init_qty);

		// Two restock methods, one method for all products
		void restock(int additional);
		//   another for specific ones
		void restock(int product, int additional);

		// check if a particular product is in stock
		bool is_instock(int product);

		// ask how many there are
		int on_hand(int product);

		// remove some number of a product (i.e. sell some)
		// returns a bool to tell if it worked
		// e.g. return false if not enough in stock
		bool remove(int product, int amt);

		//
		// Which products need to be restocked?
		// Pass in a restock level,
		// the function fills in a bool array where
		// true in position 0 => product 0 is below that level
		// true in position 1 => product 1 is below that level
		// ...
		// retrn value is number of products that need restock
		int need_restock(int minimum, bool isLow[]);

		//
		// returns the maximum valid product id
		//
		int maxid();

	private:
		// the array of counters, one per product
		int counts[NUM_PRODUCTS];

		// the size of the array; set to NUM_PRODUCTS for now
		// if we used a dynamic array instead, this would
		// store the current size
		int	size;

		// determines if a product id is valid (used internally)
		bool valid_id(int product);
};

