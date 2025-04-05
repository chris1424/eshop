This program implements an e-shop application with separate interfaces for both admins and customers. It allows the management and interaction with products and users, whether they are clients or admins. The interaction between products and 
the different types of users is, of course, different. For instance, customers have their own shopping cart where they can add products, edit and remove previously added items,complete their orders, and view them. Additionally, they can search for 
products and add them directly to their cart. A notable feature is that customers can even review their past orders stored in a file named after their username.
On the other hand, admins interact with the products in a different way. They have the ability to add new products for customers, edit existing ones, and even remove products. Another important functionality is that admins can view the 
top 5 most ordered products. Furthermore, they can check all unavailable products.
These operations were implemented using three vectors: one for users, one for products, and one for the shopping cart. The first two vectors were populated with data from the provided files, so each product that existed in the files
was added to the corresponding vector. All changes made during the program execution were applied to the vectors, not the files. The files were updated only at the end, except when a customer completes an order, in which case their 
order history is immediately updated
