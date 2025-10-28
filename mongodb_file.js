const express = require('express');
const mongoose = require('mongoose');
const bodyParser = require('body-parser');

const app = express();
app.use(bodyParser.urlencoded({ extended: true }));

// ✅ MongoDB Atlas connection
mongoose.connect('mongodb+srv://pepakayalasiva7075_db_user:Sivaganesh042@cluster0.n2ha1x9.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0', {
    useNewUrlParser: true,
    useUnifiedTopology: true
})
.then(() => console.log('✅ Connected to MongoDB'))
.catch(err => console.error('❌ MongoDB error:', err));

// ✅ Schema & Model
const studentSchema = new mongoose.Schema({
    name: String,
    age: Number,
    course: String
});
const Student = mongoose.model('Student', studentSchema);

// 🏠 Home Page (Form + View button)
app.get('/', (req, res) => {
    res.send(`
    <h2>Student Form</h2>
    <form action="/add" method="POST">
        <input name="name" placeholder="Name" required><br><br>
        <input name="age" type="number" placeholder="Age" required><br><br>
        <input name="course" placeholder="Course" required><br><br>
        <button type="submit">Add Student</button>
    </form>
    <br>
    <form action="/students" method="GET">
        <button type="submit">View All Students</button>
    </form>
    `);
});

// ➕ Add student
app.post('/add', async (req, res) => {
    const { name, age, course } = req.body;
    await Student.create({ name, age, course });
    res.redirect('/');
});

// 📖 View all students
app.get('/students', async (req, res) => {
    const students = await Student.find();
    let html = `<h2>All Students</h2>
        <table border="1" cellpadding="8">
        <tr><th>Name</th><th>Age</th><th>Course</th><th>Actions</th></tr>`;

    students.forEach(s => {
        html += `<tr>
            <td>${s.name}</td>
            <td>${s.age}</td>
            <td>${s.course}</td>
            <td>
                <a href="/edit/${s._id}">Edit</a> | 
                <a href="/delete/${s._id}" onclick="return confirm('Delete this student?')">Delete</a>
            </td>
        </tr>`;
    });

    html += `</table><br><a href="/">Back to Home</a>`;
    res.send(html);
});

// ✏️ Edit form
app.get('/edit/:id', async (req, res) => {
    const s = await Student.findById(req.params.id);
    res.send(`
    <h2>Edit Student</h2>
    <form action="/update/${s._id}" method="POST">
        <input name="name" value="${s.name}" required><br><br>
        <input name="age" type="number" value="${s.age}" required><br><br>
        <input name="course" value="${s.course}" required><br><br>
        <button type="submit">Update</button>
    </form>
    `);
});

// 🔄 Update student
app.post('/update/:id', async (req, res) => {
    await Student.findByIdAndUpdate(req.params.id, req.body);
    res.redirect('/students');
});

// ❌ Delete student
app.get('/delete/:id', async (req, res) => {
    await Student.findByIdAndDelete(req.params.id);
    res.redirect('/students');
});

// 🚀 Start server
app.listen(3000, () => console.log('🚀 Server running at http://localhost:3000'));
