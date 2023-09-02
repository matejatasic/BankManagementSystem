bank-management-system:
	g++ bank-management-system.cpp -std=c++20 ./controllers/login-controller.cpp ./controllers/customer-login-controller.cpp ./controllers/admin-login-controller.cpp ./controllers/bank-controller.cpp ./controllers/customer-controller.cpp ./controllers/admin-controller.cpp ./repositories/account-repository.cpp ./repositories/transaction-repository.cpp ./repositories/employee-repository.cpp ./models/transaction-model.cpp ./models/account-model.cpp ./models/employee-model.cpp ./services/customer-login-service.cpp ./services/admin-login-service.cpp ./services/customer-service.cpp ./services/admin-service.cpp ./services/hash-service.cpp -lsqlite3 -o bank-management-system