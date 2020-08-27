create table bots ( botid varchar(33), ip varchar(16), geo varchar(3), privileges varchar(12), user_name varchar(128), cpu_name varchar(128), domain varchar(128), last_date TIMESTAMP, infection_date TIMESTAMP );

insert INTO bots (botid,ip,geo,privileges,user_name,cpu_name,domain,last_date,infection_date) VALUES ("0a0a0a0a0a0a0a0a0a0a0a0a0a0a0", "192.168.1.1", "IR", "SYSTEM", "Usertest", "cppu test", "domain.ir", NOW(), NOW());



