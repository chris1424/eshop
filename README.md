🛒 E-Shop Application
This program implements an e-shop system with separate interfaces for admins and customers. It provides full functionality for managing and interacting with products and users.

👤 Customer Features
Customers can:

 * Maintain their own shopping cart:

    * Add products

     * Edit or remove previously added items

     * Complete orders

 * Search for products and add them directly to their cart

 * View past orders, which are stored in a file named after their username

 * Order history is saved immediately upon checkout

🛠️ Admin Features
Admins have extended control and can:

 * Add new products

 * Edit existing products

 * Remove products

 * View:

    * The top 5 most ordered products

    * A list of currently unavailable products

🧱 Internal Structure
The program uses three vectors for data handling:

 * A vector for users

 * A vector for products

 * A vector for the shopping cart

🔄 Data Flow
 * Product and user data are initially loaded from provided files

 * All actions during runtime are performed on the in-memory vectors

 * Files are only updated at the end of the program, except when a customer completes an order (in which case their order file is updated immediately)
