# Use OpenJDK 17 slim version as the base image
FROM --platform=linux/amd64 openjdk:17-jdk-slim

# Set the working directory inside the container
WORKDIR /app

# You can specify a volume in Dockerfile, but this is more for documentation purposes
# Actual volume mapping must be done during container run
VOLUME /app

# Optionally, you can add other commands to copy files, install dependencies, etc.
# COPY . /app

# Command to keep the container running (for example, start a shell)
CMD ["bash"]
